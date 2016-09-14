/**
* @file objectDetection2.cpp
* @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
* @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream - Using LBP here
* 손가락 : http://picoledelimao.github.io/blog/2015/11/15/fingertip-detection-on-opencv/ 참조
* 키보드 이미지 : http://docs.opencv.org/2.4/doc/tutorials/core/adding_images/adding_images.html 참조
*/

#include "stdafx.h"
#include "Matrix.h"
#include "Vector.h"

int main() {
	// 웹캠으로 캡처화면을 받아옴
	VideoCapture capture(0);

	if (!MATRIX->isVideoCamera(capture)) {
		return 0;
	}

	// HSV 프레임 설정
	MATRIX->setHSV();

	// 핸드팁 초기화
	VECTOR->initHandTip();

	// 화면에 나오는 이미지를 while을 돌려서 받아온다.
	bool frame_valid = true;
	while (frame_valid) {
		try {
			// 메인 프레임 초기화
			MATRIX->initMain(capture);

			if (MATRIX->isOperationBack()) {

				// differ 프레임과 and 프레임을 만듬
				MATRIX->makeFrame();

				// 메인 프레임 모폴로지 설정
				MATRIX->morphologyFrame();

				// 외곽선 찾고 그리기
				VECTOR->findDrawContours();

				// 손 인식(hand recognization. one hand or two hand)
				VECTOR->handRecognization();
				
				// 손가락 찾기(handtip detection)
				// 두 손(0, 1)을 찾음
				VECTOR->handTipDetection(0);
				VECTOR->handTipDetection(1);
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
			frame_valid = false;
		}

		//처리를 끝내고 프레임 창을 나타냄
		MATRIX->printFrame(frame_valid);

		if (waitKey(30) == 27) {
			// ESC 누르면 break
			break;
		}
	}
	if (capture.isOpened()) {
		capture.release();
	}
	destroyAllWindows();
	MATRIX->destroyInstance();
	VECTOR->destroyInstance();

	return 0;
}