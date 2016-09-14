#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"
#include "KeyBoard.h"


// ������
Vector::Vector() {
	// �հ��� ����Ʈ ���� �ʱ�ȭ
	handPointDefects = vector<int>(DEFECTS_COUNT);

	// �����̱� �� �հ��� �� ���� �ʱ�ȭ
	beforeHandTip = vector<vector<Point>>(2, vector<Point>(5));

	// ������ �� �հ��� �� ���� �ʱ�ȭ
	handTip = vector<vector<Point>>(2, vector<Point>(5));
}

void Vector::initHandTip() {
	for (int size = 0; size < 5; size++) {
		beforeHandTip[0][size] = Point(0, 0);
		beforeHandTip[1][size] = Point(0, 0);
		handTip[0][size] = Point(0, 0);
		handTip[1][size] = Point(0, 0);
	}
}

void Vector::findDrawContours() {
	// �ܰ��� ã��(Contours Detection)
	findContours(MATRIX->getContoursFrame(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	// �ܰ��� ��Ʈ���� ũ�� ����
	contSize = (int)contours.size();

	// �ܰ��� �׸���(Draw Contours)
	for (int i = 0; i < contSize; i++) {
		drawContours(MATRIX->getMainFrame(), contours, i, Scalar(128), 2, LINE_8, hierarchy);
	}
}

void Vector::handRecognization() {
	// �� �ܰ� ����(hand contours vector)�� ����
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
	KeyBoard keyboard;

	pointDefects = vector<vector<Point>>(contSize);  // �� ���ϰ��Լ�
	pointHull = vector<vector<Point>>(contSize);	 // �ܰ���

	vecDefects = vector<vector<Vec4i>>(contSize);	 // ���� ���ϰ��Լ�
	hullIndexes = vector<vector<int>>(contSize);     // �ܰ��� �ε���

	if (!handContours[i].empty()) {
		vector<Point> pointCenter(contSize);
		// ������ �ܰ��� ã�� �޼ҵ�
		// convexHull(���� ����) : �� �� ���� ��� ���� ���� ��� �����ϴ� �ֿܰ� ������ ã��
		convexHull(handContours[i], hullIndexes[i]);
		
		// convexityDefects : ������ ���� ����(�հ��� ������ �� �κ�)�� ã��
		convexityDefects(handContours[i], hullIndexes[i], vecDefects[i]);
		
		for (int j = 0; j < hullIndexes[i].size(); j++) {
			int index = hullIndexes[i][j];
			pointHull[i].push_back(handContours[i][index]);
		}

		// �հ��� ���� �� �κ�(����)�� ã��
		int count = 0;
		for (int k = 0; k < vecDefects[i].size(); k++) {
			if (vecDefects[i][k][3] > 36 * 256) { // 30 * 256

				int index0 = vecDefects[i][k][0];	//start_index
				int index1 = vecDefects[i][k][1];	//end_index
				int index2 = vecDefects[i][k][2];	//farthest_pt_index

				handPointDefects[count] = index2;
				count++;

				pointDefects[i].push_back(handContours[i][index2]);
//drw depth_point				circle(Main_frame, contours[i][index2], 3, Scalar(0, 0, 255), 3);//red

				// �� �ܰ����� ��翡 ���� �� �߾� �� ũ�⸦ �ø�
				pointCenter[i] += handContours[i][index2];
			}
		}

		// ���� �߾��� ã��(���)
		pointCenter[i].x /= count;
		pointCenter[i].y /= count;
		// ���� - �� �߾� ��ġ�� x + 10, y - 40 �̵���
		// �Ʒ� - �� �߾� ��ġ�� x + 10, y + 40 �̵���
		pointCenter[i].x += 10;
		pointCenter[i].y += 40;

		// ���� �߾ӿ� ���� �׸�
		//circle(MATRIX->getMainFrame(), pointCenter[i], 3, Scalar(0, 255, 0), 3);				// circle(Main_frame, pointCenter[i], 8*8, Scalar(0, 255, 0), 3);
		
		// ���� �����ӿ� ���� �ܰ����� �׸�
		drawContours(MATRIX->getMainFrame(), pointHull, i, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point(0, 0));
		
		// ���� �߻��� �׸����¸� �׸�
		Rect handSquare(pointCenter[i].x - 125, pointCenter[i].y - 150, 250, 160);
		rectangle(MATRIX->getMainFrame(), handSquare, Scalar(255, 255, 0));
		if (!handTip[i].empty() && i < 2) { //before value.hjhj
			for (int k = 0; k < 5; k++) {
				beforeHandTip[i][k] = handTip[i][k];
			}
		}
		// �հ��� ���̸� ����
		double preDist = 0, nextDist = 0, currDist = 0;
		int tipCount = 0;

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
		// �հ��� ���� ���� ����
		for (int t = 0; t < tipCount; t++) {
			circle(MATRIX->getMainFrame(), handTip[i][t], 5, Scalar(255, 0, 0), 3);
		}
		// �հ������� Ű�� ������ keyBoardInput ����
		if (!handTip[i].empty()) {
			for (int k = 0; k < 5; k++) {
				if ((handTip[i][k].y - beforeHandTip[i][k].y) > 10 && (handTip[i][k].y - beforeHandTip[i][k].y) < 30
					&& (handTip[i][k].x - beforeHandTip[i][k].x < 20) && (handTip[i][k].x - beforeHandTip[i][k].x >(-20))) {

					/* keyboard input function.*/
					keyboard.keyBoardInput(beforeHandTip[i][k].x, beforeHandTip[i][k].y);
					break;
				}
			}
		}
	}
}

float Vector::innerAngle(float px1, float py1, float px2, float py2, float cx1, float cy1)
{
	float dist1 = sqrt((px1 - cx1)*(px1 - cx1) + (py1 - cy1)*(py1 - cy1));
	float dist2 = sqrt((px2 - cx1)*(px2 - cx1) + (py2 - cy1)*(py2 - cy1));

	float Ax, Ay;
	float Bx, By;
	float Cx, Cy;

	//find closest point to C  
	//printf("dist = %lf %lf\n", dist1, dist2);  

	Cx = cx1;
	Cy = cy1;
	if (dist1 < dist2)
	{
		Bx = px1;
		By = py1;
		Ax = px2;
		Ay = py2;
	}
	else {
		Bx = px2;
		By = py2;
		Ax = px1;
		Ay = py1;
	}
	float Q1 = Cx - Ax;
	float Q2 = Cy - Ay;
	float P1 = Bx - Ax;
	float P2 = By - Ay;

	float A = acos((P1*Q1 + P2*Q2) / (sqrt(P1*P1 + P2*P2) * sqrt(Q1*Q1 + Q2*Q2)));
	A = A * 180 / (float)CV_PI;

	return A;
}


void Vector::handTipDetectWithAngle() {
	
}


// �Ҹ���
Vector::~Vector() { }