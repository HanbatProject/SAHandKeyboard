/*
* ���콺
*/
#include "stdafx.h"
#include "Mouse.h"
#include "Matrix.h"


// ������
Mouse::Mouse() {}

// ���콺 ����
void Mouse::onMouse(int event, int x, int y, int flag, void* param) {
	Mat* Back = (Mat*)param;
	switch (event) {
	case CV_EVENT_LBUTTONDOWN:
		cout << "Left Button Down X = " << x << ", Y = " << y << endl;
		MATRIX->callbackMouse(Back);
		break;
	case CV_EVENT_RBUTTONDOWN:
		MATRIX->setOperationBack(true);
		break;
	}
	return;
}

// �Ҹ���
Mouse::~Mouse() {}