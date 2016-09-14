/*
* ��Ʈ���� ���
*/
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "stdafx.h"
#include "TemplateSingleton.h"
#include "KeyBoard.h"


class Matrix : public TemplateSingleton<Matrix> {
public:
	const int BLUR_ELEMENT_SIZE = 3;
	// int minH = 130, maxH = 160, minS = 10, maxS = 40, minV = 7, maxV = 130;
	// Default HSV�� �����Ѵ�. ���� ���� �ִ� default
    int minH = 2, maxH = 23;
	int minS = 13, maxS = 140;
	int minV = 70, maxV = 255;
private:
	bool operationBack = false;

	// ��� ��Ʈ����
	Mat background;

	// �⺻ ������
	Mat Main_frame;
	Mat and_frame;
	Mat hsv_frame;
	Mat binary_frame;

	// ��� ������
	Mat differ_frame;

	// �������� ������
	Mat morphology_frame;
	Mat blur_erode_frame;

	// �ܰ��� ������
	Mat contours_frame;

	// �� ������Ʈ
	Mat blurElement;

	// Ű���� �̹���
	Mat keyBoardImage;
	Mat dst;

	// Mat YCrCb_frame;
	// Mat blur_dilate_frame;
	// Mat before_contours_frame;
	// Mat binary_blur_frame;

public:
	Matrix();
	bool isVideoCamera(VideoCapture);
	bool isOperationBack();

	void setHSV();
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