/*
* 매트릭스 헤더
*/
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "stdafx.h"
#include "TemplateSingleton.h"


class Matrix : public TemplateSingleton<Matrix> {
private:
	const int BLUR_ELEMENT_SIZE = 3;
	// int minH = 130, maxH = 160, minS = 10, maxS = 40, minV = 7, maxV = 130;
	// Default HSV를 설정한다. 위는 원래 있던 default
    int minH = 2, maxH = 36;
	int minS = 13, maxS = 196;
	int minV = 120, maxV = 255;
private:
	bool operationBack = false;

	// 배경 매트릭스
	Mat background;

	// 기본 프레임
	Mat Main_frame;
	Mat and_frame;
	Mat hsv_frame;
	Mat binary_frame;

	// 배경 프레임
	Mat differ_frame;

	// 모폴로지 프레임
	Mat morphology_frame;
	Mat blur_erode_frame;

	// 외곽선 프레임
	Mat contours_frame;

	// 블러 엘레먼트
	Mat blurElement;

	// 키보드 이미지
	Mat keyBoardImage;

	// Mat YCrCb_frame;
	// Mat blur_dilate_frame;
	// Mat before_contours_frame;
	// Mat binary_blur_frame;

public:
	Matrix();
	bool isVideoCamera(VideoCapture);
	bool isOperationBack();

	void setHSVTrackbar();
	void initMain(VideoCapture&);
	void makeFrame();
	void morphologyFrame();
	void printFrame(bool);
	void callbackMouse(Mat* back);

	// getters
	Mat getMainFrame();
	Mat getContoursFrame();

	// setters
	void setOperationBack(bool);

	~Matrix();
};

#endif // !_MATRIX_H_