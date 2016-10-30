#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"


// 생성자
Vector::Vector() {
	// 손가락 포인트 벡터 초기화
	handPointDefects = vector<int>(DEFECTS_COUNT);

	// 움직이기 전 손가락 원 갯수 초기화
	beforeHandTip = vector<vector<Point>>(2, vector<Point>(10));

	// 움직인 후 손가락 원 갯수 초기화
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

// 손 자체 외곽선 찾기(Contours Detection)
void Vector::findDrawContours() {	
	findContours(MATRIX->getContoursFrame(), contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// 외곽선 매트릭스 크기 저장
	contSize = (int)contours.size();

	// 외곽선 그리기(Draw Contours)
	//for (int i = 0; i < contSize; i++) {
	//	drawContours(MATRIX->getMainFrame(), contours, i, Scalar(128), 2, LINE_8, hierarchy);
	//}
}

// 손 외곽 벡터(hand contours vector)를 구함
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

	pointDefects = vector<vector<Point>>(contSize);  // 점 볼록결함선
	pointHull = vector<vector<Point>>(contSize);	 // 외곽선

	vecDefects = vector<vector<Vec4i>>(contSize);	 // 벡터 볼록결함선
	hullIndexes = vector<vector<int>>(contSize);     // 외곽선 인덱스

	vector<Point> pointCenter(contSize);
	// 볼록한 외곽을 찾는 메소드
	// convexHull(볼록 껍질) : 몇 개 점을 골라 안의 점을 모두 포함하는 최외곽 점들을 찾음
	convexHull(handContours[i], hullIndexes[i], false, false);
		
	// convexityDefects : 볼록한 데서 결함(손가락 사이의 들어간 부분)을 찾음
	convexityDefects(handContours[i], hullIndexes[i], vecDefects[i]);
		
	//for (int j = 0; j < hullIndexes[i].size(); j++) {
	//	int index = hullIndexes[i][j];
	//	pointHull[i].push_back(handContours[i][index]);
	//}

	// 손가락 사이 들어간 부분(결점)을 찾음
	int start, end, farthest;
	int count = 0;
	for (int k = 0; k < vecDefects[i].size(); k++) {
		if (vecDefects[i][k][3] > 36 * 256) { // 30 * 256
			start = vecDefects[i][k][0];	//start_index
			end = vecDefects[i][k][1];	//end_index
			farthest = vecDefects[i][k][2];	//farthest_pt_index

			// 손가락 끝점을 넣음
			tempHandTip[i][count] = handContours[i][end];

			// 결점 포인트를 넣음
			handPointDefects[count] = farthest;
			count++;

			pointDefects[i].push_back(handContours[i][farthest]);
			// 들어간 부분에 원을 그림
			//circle(MATRIX->getMainFrame(), handContours[i][end], 3, Scalar(0, 0, 255), 3);
			// 손 외곽선의 모양에 따른 손 중앙 점 크기를 늘림
			pointCenter[i] += handContours[i][farthest];
		}
	}

	// 손의 중앙을 찾음(평균)
	pointCenter[i].x /= count;
	pointCenter[i].y /= count;
	// 위쪽 - 점 중앙 위치를 x + 10, y - 40 이동함
	// 아래 - 점 중앙 위치를 x + 10, y + 40 이동함
	pointCenter[i].x += 10;
	pointCenter[i].y += 40;

	// 손가락 끝을 그림
	handTipDrawer(pointCenter, count, i);

	// 손가락으로 키를 누르면 keyBoardInput 동작
	keyBoardInput(count, i);
}

void Vector::handTipDrawer(vector<Point> pointCenter, int count, int i) {
	// 손의 중앙에 원을 그림
	//circle(Main_frame, pointCenter[i], 8*8, Scalar(0, 255, 0), 3);
	//circle(MATRIX->getMainFrame(), pointCenter[i], 3, Scalar(0, 255, 0), 3);

	// 메인 프레임에 손의 외곽선을 그림
	//drawContours(MATRIX->getMainFrame(), pointHull, i, Scalar(0, 255, 0),
	//				2, 8, hierarchy, 0, Point(0, 0));

	// 손의 네모형태를 그림
	Rect handSquare(pointCenter[i].x - 125, pointCenter[i].y - 150, 250, 160);
	//rectangle(MATRIX->getMainFrame(), handSquare, Scalar(255, 255, 0));
	if (!handTip[i].empty() && i < 2) { //before value.hjhj
		for (int k = 0; k < count; k++) {
			beforeHandTip[i][k] = handTip[i][k];
		}
	}
	// 손가락 끝점을 구함
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

	// 손가락 끝의 원을 만듬
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

// 소멸자
Vector::~Vector() { }