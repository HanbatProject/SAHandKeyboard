/**
* @file objectDetection2.cpp
* @author A. Huaman ( based in the classic facedetect.cpp in samples/c )
* @brief A simplified version of facedetect.cpp, show how to load a cascade classifier and how to find objects (Face + eyes) in a video stream - Using LBP here
*/

#include "stdafx.h"
#include "Matrix.h"
#include "Vector.h"

int main() {
	// ��ķ���� ĸóȭ���� �޾ƿ�
	VideoCapture capture(0);

	if (!MATRIX->isVideoCamera(capture)) {
		return 0;
	}

	// HSV ��ȯ�� ������ Ʈ���� ����
	MATRIX->setHSVTrackbar();

	// �ڵ��� �ʱ�ȭ
	VECTOR->initHandTip();

	// ȭ�鿡 ������ �̹����� while�� ������ �޾ƿ´�.
	bool frame_valid = true;
	while (frame_valid) {
		try {
			// ���� ������ �ʱ�ȭ
			MATRIX->initMain(capture);

			if (MATRIX->isOperationBack()) {

				// differ �����Ӱ� and �������� ����
				MATRIX->makeFrame();

				// ���� ������ �������� ����
				MATRIX->morphologyFrame();

				// �ܰ��� ã�� �׸���
				VECTOR->findDrawContours();

				// �� �ν�(hand recognization. one hand or two hand)
				VECTOR->handRecognization();
				
				// �հ��� ã��(handtip detection)
				// �� ��(0, 1)�� ã��
				VECTOR->handTipDetection(0);
				VECTOR->handTipDetection(1);
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
			frame_valid = false;
		}

		//ó���� ������ ������ â�� ���
		MATRIX->printFrame(frame_valid);

		// ESC ������ break
		if (waitKey(30) == 27) {
			break;
		}
	}

	// ���� �۾�
	if (capture.isOpened()) {
		capture.release();
	}
	destroyAllWindows();
	MATRIX->destroyInstance();
	VECTOR->destroyInstance();

	return 0;
}