/*
* 벡터 헤더
*/
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "stdafx.h"
#include "TemplateSingleton.h"
#include "KeyBoard.h"

class Vector : public TemplateSingleton<Vector> {
private:
	const int DEFECTS_COUNT = 8;
	const int CONTOUR_AREA_MIN = 4000;
	// Contours(윤곽) 필드
	// 벡터 포인트형 벡터(점들이 모여서 선이 되는 원리)
	// 기본 외곽 벡터
	vector<vector<Point>> contours;

	// 손 외곽 벡터
	vector<vector<Point>> handContours;	 

	// 선을 감지하기 위한 벡터
	vector<Vec4i> hierarchy;

	// 움직이기 전 화면 손가락 크기들
	vector<vector<Point>> beforeHandTip;

	// 움직인 후 손가락 크기들
	vector<vector<Point>> handTip;

	// 임시 손가락 크기들
	vector<vector<Point>> tempHandTip;

	// 볼록결함 - 움푹 들어간 부분 (ConvexityDefects)

	/*
	*	Vec4i vecDefects
	*	[0] start_index
	*	[1] end_index
	*	[2] farthest_pt_index
	*	[3] fixpt_depth
	*/
	vector<vector<Point>> pointDefects;  // 볼록결함 점들의 선 벡터
	vector<vector<Vec4i>> vecDefects;	 // 볼록결함 벡터를 저장하는 선 벡터
	vector<int> handPointDefects;		 // 움푹 들어간 부분을 최종 저장할 벡터

	vector<vector<Point>> pointHull;	 // 외곽선
	vector<vector<int>> hullIndexes;     // 외곽선 인덱스
	int contSize = 0; // contours 크기

	// 키보드
	KeyBoard keyboard;

public:
	Vector();
	void initHandTip();
	void findDrawContours();
	void handRecognization();
	void handTipDetection(int);
	void handTipDrawer(vector<Point>, int, int);
	void keyBoardInput(int, int);

	~Vector();
};

#endif // !_VECTOR_H_