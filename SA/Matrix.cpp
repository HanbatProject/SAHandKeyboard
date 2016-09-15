#include "stdafx.h"
#include "Matrix.h"
#include "KeyBoard.h"
#include "Mouse.h"

// 생성자
Matrix::Matrix() {
	// 키보드 이미지 설정
	keyBoardImage = imread("keyboard.png");
}

// booleans
bool Matrix::isVideoCamera(VideoCapture capture) {
	if (!capture.isOpened()) {
		cerr << "카메라가 연결되어 있지 않습니다!" << endl;
		return false;
	}
	return true;
}

bool Matrix::isOperationBack() {
	return operationBack;
}

// getters
Mat Matrix::getMainFrame()
{
	return Main_frame;
}

Mat Matrix::getContoursFrame()
{
	return contours_frame;
}

// HSV 창을 설정한다
void Matrix::setHSVTrackbar() {
	// 프레임 창 이름을 설정한다.
	namedWindow(HSV_FRAME_CAM);

	// 트랙바 설정
	createTrackbar("MinH", HSV_FRAME_CAM, &minH, 180);
	createTrackbar("MaxH", HSV_FRAME_CAM, &maxH, 180);
	createTrackbar("MinS", HSV_FRAME_CAM, &minS, 255);
	createTrackbar("MaxS", HSV_FRAME_CAM, &maxS, 255);
	createTrackbar("MinV", HSV_FRAME_CAM, &minV, 255);
	createTrackbar("MAxV", HSV_FRAME_CAM, &maxV, 255);
}

void Matrix::initMain(VideoCapture& capture) {
	// 웹캠 캡처 화면을 메인프레임에 삽입한다.
	capture >> Main_frame;

	// 좌우로 뒤집음. flipCode = 세로는 0, 좌우는 1, 상하좌우는 -1
	flip(Main_frame, Main_frame, -1);

	//RGB를 HSV로 변환하는 메소드
	cvtColor(Main_frame, hsv_frame, CV_BGR2HSV);

	// inRange 메소드는 임계값(threshold)에서 우리가 받고 싶어하는 이미지를 이진으로 받아와준다.
	inRange(hsv_frame, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), binary_frame);
}

void Matrix::makeFrame() {
	// 원래 화면에서 이진프레임을 빼준다.
	differ_frame = binary_frame - background;

	// 이진프레임과 원래 화면에서 이진 프레임을 빼준 화면을 AND 연산해준다.
	and_frame = differ_frame & binary_frame;
}

void Matrix::morphologyFrame()
{
	// 손가락을 블러처리한다.
	blurElement = getStructuringElement(MORPH_ELLIPSE,							// MORPH_RECT,
		Size(2*BLUR_ELEMENT_SIZE + 1, 2*BLUR_ELEMENT_SIZE + 1),
		Point(BLUR_ELEMENT_SIZE, BLUR_ELEMENT_SIZE));

	// 모폴로지(영상을 형태학적 관점으로 보는 것) 기법을 이용하도록 오픈한다.
	morphologyEx(and_frame, morphology_frame, MORPH_OPEN, blurElement);
	
	// MORPH_RECT로 한번더 블러처리한다.
	//blurElement = getStructuringElement(MORPH_RECT,								// MORPH_ELLIPSE,
	//	Size(2*BLUR_ELEMENT_SIZE + 1, 2*BLUR_ELEMENT_SIZE + 1),						// Size(2*BLUR_ELEMENT_SIZE +1
	//	Point(BLUR_ELEMENT_SIZE, BLUR_ELEMENT_SIZE));

	// 영상을 부드럽게 만든다.
	GaussianBlur(morphology_frame, morphology_frame, Size(2 * BLUR_ELEMENT_SIZE + 1, 2 * BLUR_ELEMENT_SIZE  + 1), 5);
	medianBlur(morphology_frame, morphology_frame, 5);
	
	//morphology_frame.copyTo(blur_erode_frame);

	// 영상을 팽창(배경 축소, 물체 크기 확장)한다.
	dilate(morphology_frame, blur_erode_frame, blurElement);

	// 영상을 2번 침식(배경 확장, 물체 크기 축소)한다.
	erode(morphology_frame, blur_erode_frame, blurElement);
	erode(morphology_frame, blur_erode_frame, blurElement);
	blur_erode_frame.copyTo(contours_frame);
}

void Matrix::printFrame(bool frame_valid) {
	KeyBoard keyboard;
	Mouse mouse;
	if (!frame_valid) {
		return;
	}

	try {
		// 키보드 사각형
		//keyboard.keyBoardReg(Main_frame);

		// 마우스
		setMouseCallback(MAIN_FRAME, mouse.onMouse, (void*)&Main_frame);

		// 키보드 이미지 추가(alpha = 메인 투명도값, beta = 키보드 투명도값)
		addWeighted(Main_frame, keyboard.getAlpha(), keyBoardImage, keyboard.getBeta(), 0.0, Main_frame);
		imshow(MAIN_FRAME, Main_frame);
		imshow(HSV_FRAME_CAM, hsv_frame);
		imshow(BINARY_FRAME, binary_frame);
		if (!background.empty()) {
			//imshow("back", background);
		}
		if (!differ_frame.empty()) {
			imshow("erode", blur_erode_frame);
			//imshow("morphology", morphology_frame);
		}
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
}

void Matrix::callbackMouse(Mat* back) {
	cvtColor(*back, *back, CV_BGR2HSV);
	inRange(*back, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), *back);
	//*Back.copyTo(background); 
	background = *back;
}

void Matrix::setOperationBack(bool pram) {
	this->operationBack = pram;
	return;
}

// 소멸자
Matrix::~Matrix() { }
