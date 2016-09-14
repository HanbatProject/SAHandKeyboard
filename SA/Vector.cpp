#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"


// 생성자
Vector::Vector() {
	// 손가락 포인트 벡터 초기화
	handPointDefects = vector<int>(7);

	// 움직이기 전 화면 손가락 크기들의 원 초기화
	beforeHandTip = vector<vector<Point>>(2, vector<Point>(5));

	// 움직인 후 손가락 크기들 원 초기화
	handTip = vector<vector<Point>>(2, vector<Point>(5));
}

void Vector::initHandTip() {
	for (int size = 0; size < 5; size++) {
		beforeHandTip[0][size] = Point(0, 0);
	}
	for (int size = 0; size < 5; size++) {
		beforeHandTip[1][size] = Point(0, 0);
	}

	for (int size = 0; size < 5; size++) {
		handTip[0][size] = Point(0, 0);
	}
	for (int size = 0; size < 5; size++) {
		handTip[1][size] = Point(0, 0);
	}
}

void Vector::findDrawContours() {
	// 외곽선 찾기(Contours Detection)
	findContours(MATRIX->getContoursFrame(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 외곽선 매트릭스 크기 저장
	contSize = (int)contours.size();
	
	// 외곽선 그리기(Draw Contours)
	for (int i = 0; i < contSize; i++) {
		drawContours(MATRIX->getMainFrame(), contours, i, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point());
	}
}

void Vector::handRecognization() {
	intVecDefects = vector<vector<Vec4i>>(contSize); // 벡터 볼록결함선
	pointDefects = vector<vector<Point>>(contSize);  // 점 볼록결함선
	pointHull = vector<vector<Point>>(contSize);	  // 외곽선
	hullIndexes = vector<vector<int>>(contSize);   // 외곽선 인덱스
														  // 손 외곽 벡터(hand contours vector)
	handContours = vector<vector<Point>>(2);
	for (int i = 0; i < contSize; i++) {
		//					std::cout << "Size " << endl;
		if (contourArea(contours[i]) > 4000) {
			if (handContours[0].empty()) {
				handContours[0].resize(contours[i].size());
				handContours[0] = contours[i];	//
			}
			else {
				handContours[1].resize(contours[i].size());
				handContours[1] = contours[i];	//
			}
		}
	}
}

void Vector::handTipDetection(int i) {
	KeyBoard keyboard;
	//					std::cout << "for " << endl;
	if (!handContours[i].empty()) {
		vector<Point> pointCenter(contSize);
		// 볼록한 외곽을 찾는 메소드
		// convexHull(볼록 껍질) : 몇 개 점을 골라 안의 점을 모두 포함하는 최외곽 점들을 찾음
		convexHull(handContours[i], hullIndexes[i]);
		
		// convexityDefects : 볼록한 데서 결함(손가락 사이의 들어간 부분)을 찾음
		convexityDefects(handContours[i], hullIndexes[i], intVecDefects[i]);
		
		for (int j = 0; j < hullIndexes[i].size(); j++) {
			int index = hullIndexes[i][j];
			// push_back은 괄호 안의 파라미터를 복사하거나 옮기겠다는 것을 의미한다.
			pointHull[i].push_back(handContours[i][index]);
		}

		// 결점 깊이를 찾는 루틴?
		int count = 0;
		for (int k = 0; k < intVecDefects[i].size(); k++) {
			if (intVecDefects[i][k][3] > 30 * 256) {

				int index0 = intVecDefects[i][k][0];	//start_index
				int index1 = intVecDefects[i][k][1];	//end_index
				int index2 = intVecDefects[i][k][2];	//farthest_pt_index

				handPointDefects[count] = index2;
				count++;

				pointDefects[i].push_back(handContours[i][index2]);
//drw depth_point				circle(Main_frame, contours[i][index2], 3, Scalar(0, 0, 255), 3);//red
				pointCenter[i] += handContours[i][index2];
			}
		}

		// 손의 중앙을 찾음(평균)
		pointCenter[i].x /= count;
		pointCenter[i].y /= count;
		// 점 중앙 크기를 변환함
		pointCenter[i].x += 10;
		pointCenter[i].y -= 40;

		// 메인 프레임에 원을 그림
		circle(MATRIX->getMainFrame(), pointCenter[i], 3, Scalar(0, 255, 0), 3);				// circle(Main_frame, pointCenter[i], 8*8, Scalar(0, 255, 0), 3);
		
		// 메인 프레임에 손의 외곽선을 그림
		//drawContours(MATRIX->getMainFrame(), pointHull, i, Scalar(0, 255, 0), 2, 8, hierarchy, 0, Point());
		
		// 손의 추상적 네모형태를 그림
		Rect handSquare((pointCenter[i].x - 100), pointCenter[i].y, 200, 120);
		//rectangle(MATRIX->getMainFrame(), handSquare, Scalar(255, 255, 0));
		if (!handTip[i].empty() && i < 2) { //before value.hjhj
			for (int k = 0; k < 5; k++) {
				beforeHandTip[i][k] = handTip[i][k];
			}
		}
		// 손가락 길이를 구함
		int preDist = 0, nextDist = 0, currDist = 0;
		int tipCount = 0;

		for (int a = 1; a < handContours[i].size() - 1; a++) {
			if (handContours[i][a].inside(handSquare)) {
				preDist = (int)(pow(pointCenter[i].x - handContours[i][a - 1].x, 2)
					       + pow(pointCenter[i].y - handContours[i][a - 1].y, 2));
				currDist = (int)(pow(pointCenter[i].x - handContours[i][a].x, 2)
					       + pow(pointCenter[i].y - handContours[i][a].y, 2));
				nextDist = (int)(pow(pointCenter[i].x - handContours[i][a + 1].x, 2)
					       + pow(pointCenter[i].y - handContours[i][a + 1].y, 2));

				if (currDist > preDist && currDist > nextDist && currDist > 64 * 64) { //handTip detection.

					handTip[i][tipCount] = handContours[i][a];
					tipCount++;

					if (tipCount >= 5) break;

					a = handPointDefects[tipCount];
				}
			}
		}
		// 손가락 원을 만듬
		for (int t = 0; t < tipCount; t++) {
			circle(MATRIX->getMainFrame(), handTip[i][t], 5, Scalar(255, 0, 0), 5);
		}
		// 손가락으로 키를 누르면 keyBoardInput 동작
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


// 소멸자
Vector::~Vector() { }