#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"


// ������
Vector::Vector() {
	// �հ��� ����Ʈ ���� �ʱ�ȭ
	handPointDefects = vector<int>(DEFECTS_COUNT);

	// �����̱� �� �հ��� �� ���� �ʱ�ȭ
	beforeHandTip = vector<vector<Point>>(2, vector<Point>(10));

	// ������ �� �հ��� �� ���� �ʱ�ȭ
	handTip = vector<vector<Point>>(2, vector<Point>(10));

	tempHandTip = vector<vector<Point>>(2, vector<Point>(10));
}

void Vector::initHandTip() {
	for (int size = 0; size < 5; size++) {
		beforeHandTip[0][size] = Point(0, 0);
		beforeHandTip[1][size] = Point(0, 0);
		handTip[0][size] = Point(0, 0);
		handTip[1][size] = Point(0, 0);
		tempHandTip[0][size] = Point(0, 0);
		tempHandTip[1][size] = Point(0, 0);
	}
}

// �� ��ü �ܰ��� ã��(Contours Detection)
void Vector::findDrawContours() {	
	findContours(MATRIX->getContoursFrame(), contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// �ܰ��� ��Ʈ���� ũ�� ����
	contSize = (int)contours.size();

	// �ܰ��� �׸���(Draw Contours)
	//for (int i = 0; i < contSize; i++) {
	//	drawContours(MATRIX->getMainFrame(), contours, i, Scalar(128), 2, LINE_8, hierarchy);
	//}
}

// �� �ܰ� ����(hand contours vector)�� ����
void Vector::handRecognization() {
	handContours = vector<vector<Point>>(2);
	for (int i = 0; i < contSize; i++) {
		if (contourArea(contours[i]) > CONTOUR_AREA_MIN) {
			if (handContours[0].empty()) {
				handContours[0].resize(contours[i].size());
				handContours[0] = contours[i];
			}
			else {
				handContours[1].resize(contours[i].size());
				handContours[1] = contours[i];
			}
		}
	}
}

void Vector::handTipDetection(int i) {
	if (handContours[i].empty()) {
		return;
	}

	pointDefects = vector<vector<Point>>(contSize);  // �� ���ϰ��Լ�
	pointHull = vector<vector<Point>>(contSize);	 // �ܰ���

	vecDefects = vector<vector<Vec4i>>(contSize);	 // ���� ���ϰ��Լ�
	hullIndexes = vector<vector<int>>(contSize);     // �ܰ��� �ε���

	vector<Point> pointCenter(contSize);
	// ������ �ܰ��� ã�� �޼ҵ�
	// convexHull(���� ����) : �� �� ���� ��� ���� ���� ��� �����ϴ� �ֿܰ� ������ ã��
	convexHull(handContours[i], hullIndexes[i], false, false);
		
	// convexityDefects : ������ ���� ����(�հ��� ������ �� �κ�)�� ã��
	convexityDefects(handContours[i], hullIndexes[i], vecDefects[i]);
		
	//for (int j = 0; j < hullIndexes[i].size(); j++) {
	//	int index = hullIndexes[i][j];
	//	pointHull[i].push_back(handContours[i][index]);
	//}

	// �հ��� ���� �� �κ�(����)�� ã��
	int start, end, farthest;
	int count = 0;
	for (int k = 0; k < vecDefects[i].size(); k++) {
		if (vecDefects[i][k][3] > 36 * 256) { // 30 * 256
			start = vecDefects[i][k][0];	//start_index
			end = vecDefects[i][k][1];	//end_index
			farthest = vecDefects[i][k][2];	//farthest_pt_index

			// �հ��� ������ ����
			tempHandTip[i][count] = handContours[i][end];

			// ���� ����Ʈ�� ����
			handPointDefects[count] = farthest;
			count++;

			pointDefects[i].push_back(handContours[i][farthest]);
			// �� �κп� ���� �׸�
			//circle(MATRIX->getMainFrame(), handContours[i][end], 3, Scalar(0, 0, 255), 3);
			// �� �ܰ����� ��翡 ���� �� �߾� �� ũ�⸦ �ø�
			pointCenter[i] += handContours[i][farthest];
		}
	}

	// ���� �߾��� ã��(���)
	pointCenter[i].x /= count;
	pointCenter[i].y /= count;
	// ���� - �� �߾� ��ġ�� x + 10, y - 40 �̵���
	// �Ʒ� - �� �߾� ��ġ�� x + 10, y + 40 �̵���
	pointCenter[i].x += 10;
	pointCenter[i].y += 40;

	// �հ��� ���� �׸�
	handTipDrawer(pointCenter, count, i);

	// �հ������� Ű�� ������ keyBoardInput ����
	keyBoardInput(count, i);
}

void Vector::handTipDrawer(vector<Point> pointCenter, int count, int i) {
	// ���� �߾ӿ� ���� �׸�
	//circle(Main_frame, pointCenter[i], 8*8, Scalar(0, 255, 0), 3);
	//circle(MATRIX->getMainFrame(), pointCenter[i], 3, Scalar(0, 255, 0), 3);

	// ���� �����ӿ� ���� �ܰ����� �׸�
	//drawContours(MATRIX->getMainFrame(), pointHull, i, Scalar(0, 255, 0),
	//				2, 8, hierarchy, 0, Point(0, 0));

	// ���� �׸����¸� �׸�
	Rect handSquare(pointCenter[i].x - 125, pointCenter[i].y - 150, 250, 160);
	//rectangle(MATRIX->getMainFrame(), handSquare, Scalar(255, 255, 0));
	if (!handTip[i].empty() && i < 2) { //before value.hjhj
		for (int k = 0; k < count; k++) {
			beforeHandTip[i][k] = handTip[i][k];
		}
	}
	// �հ��� ������ ����
	for (int a = 0; a < count; a++) {
		if (handContours[i][a].inside(handSquare)) {
			handTip[i][a] = tempHandTip[i][a];
		}
	}

	/*
	double preDist = 0, nextDist = 0, currDist = 0;
	for (int a = 1; a < handContours[i].size() - 1; a++) {
	if (handContours[i][a].inside(handSquare)) {
	preDist = pow(pointCenter[i].x - handContours[i][a - 1].x, 2)
	+ pow(pointCenter[i].y - handContours[i][a - 1].y, 2);
	currDist = pow(pointCenter[i].x - handContours[i][a].x, 2)
	+ pow(pointCenter[i].y - handContours[i][a].y, 2);
	nextDist = pow(pointCenter[i].x - handContours[i][a + 1].x, 2)
	+ pow(pointCenter[i].y - handContours[i][a + 1].y, 2);
	if (currDist > preDist && currDist > nextDist && currDist > 64 * 64) { //handTip detection.
	handTip[i][tipCount] = handContours[i][a];
	tipCount++;

	if (tipCount >= 5) break;

	a = handPointDefects[tipCount];
	}
	}
	}
	*/

	// �հ��� ���� ���� ����
	for (int t = 0; t < count; t++) {
		circle(MATRIX->getMainFrame(), handTip[i][t], 5, Scalar(255, 0, 0), 3);
	}
}

void Vector::keyBoardInput(int count, int i) {
	if (handTip[i].empty()) {
		return;
	}
	for (int k = 0; k < count; k++) {
		if ((handTip[i][k].y - beforeHandTip[i][k].y) > 9
			&& (handTip[i][k].y - beforeHandTip[i][k].y) < 15) {
			if ((handTip[i][k].x - beforeHandTip[i][k].x < 5)
				&& (handTip[i][k].x - beforeHandTip[i][k].x > -5)) {
				keyboard.keyBoardInput(handTip[i][k].x, handTip[i][k].y);
				break;
			}
		}
	}
}

// �Ҹ���
Vector::~Vector() { }