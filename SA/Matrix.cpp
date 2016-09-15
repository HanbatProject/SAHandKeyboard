#include "stdafx.h"
#include "Matrix.h"
#include "KeyBoard.h"
#include "Mouse.h"

// ������
Matrix::Matrix() {
	// Ű���� �̹��� ����
	keyBoardImage = imread("keyboard.png");
}

// booleans
bool Matrix::isVideoCamera(VideoCapture capture) {
	if (!capture.isOpened()) {
		cerr << "ī�޶� ����Ǿ� ���� �ʽ��ϴ�!" << endl;
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

// HSV â�� �����Ѵ�
void Matrix::setHSVTrackbar() {
	// ������ â �̸��� �����Ѵ�.
	namedWindow(HSV_FRAME_CAM);

	// Ʈ���� ����
	createTrackbar("MinH", HSV_FRAME_CAM, &minH, 180);
	createTrackbar("MaxH", HSV_FRAME_CAM, &maxH, 180);
	createTrackbar("MinS", HSV_FRAME_CAM, &minS, 255);
	createTrackbar("MaxS", HSV_FRAME_CAM, &maxS, 255);
	createTrackbar("MinV", HSV_FRAME_CAM, &minV, 255);
	createTrackbar("MAxV", HSV_FRAME_CAM, &maxV, 255);
}

void Matrix::initMain(VideoCapture& capture) {
	// ��ķ ĸó ȭ���� ���������ӿ� �����Ѵ�.
	capture >> Main_frame;

	// �¿�� ������. flipCode = ���δ� 0, �¿�� 1, �����¿�� -1
	flip(Main_frame, Main_frame, -1);

	//RGB�� HSV�� ��ȯ�ϴ� �޼ҵ�
	cvtColor(Main_frame, hsv_frame, CV_BGR2HSV);

	// inRange �޼ҵ�� �Ӱ谪(threshold)���� �츮�� �ް� �;��ϴ� �̹����� �������� �޾ƿ��ش�.
	inRange(hsv_frame, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), binary_frame);
}

void Matrix::makeFrame() {
	// ���� ȭ�鿡�� ������������ ���ش�.
	differ_frame = binary_frame - background;

	// ���������Ӱ� ���� ȭ�鿡�� ���� �������� ���� ȭ���� AND �������ش�.
	and_frame = differ_frame & binary_frame;
}

void Matrix::morphologyFrame()
{
	// �հ����� ��ó���Ѵ�.
	blurElement = getStructuringElement(MORPH_ELLIPSE,							// MORPH_RECT,
		Size(2*BLUR_ELEMENT_SIZE + 1, 2*BLUR_ELEMENT_SIZE + 1),
		Point(BLUR_ELEMENT_SIZE, BLUR_ELEMENT_SIZE));

	// ��������(������ �������� �������� ���� ��) ����� �̿��ϵ��� �����Ѵ�.
	morphologyEx(and_frame, morphology_frame, MORPH_OPEN, blurElement);
	
	// MORPH_RECT�� �ѹ��� ��ó���Ѵ�.
	//blurElement = getStructuringElement(MORPH_RECT,								// MORPH_ELLIPSE,
	//	Size(2*BLUR_ELEMENT_SIZE + 1, 2*BLUR_ELEMENT_SIZE + 1),						// Size(2*BLUR_ELEMENT_SIZE +1
	//	Point(BLUR_ELEMENT_SIZE, BLUR_ELEMENT_SIZE));

	// ������ �ε巴�� �����.
	GaussianBlur(morphology_frame, morphology_frame, Size(2 * BLUR_ELEMENT_SIZE + 1, 2 * BLUR_ELEMENT_SIZE  + 1), 5);
	medianBlur(morphology_frame, morphology_frame, 5);
	
	//morphology_frame.copyTo(blur_erode_frame);

	// ������ ��â(��� ���, ��ü ũ�� Ȯ��)�Ѵ�.
	dilate(morphology_frame, blur_erode_frame, blurElement);

	// ������ 2�� ħ��(��� Ȯ��, ��ü ũ�� ���)�Ѵ�.
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
		// Ű���� �簢��
		//keyboard.keyBoardReg(Main_frame);

		// ���콺
		setMouseCallback(MAIN_FRAME, mouse.onMouse, (void*)&Main_frame);

		// Ű���� �̹��� �߰�(alpha = ���� ������, beta = Ű���� ������)
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

// �Ҹ���
Matrix::~Matrix() { }
