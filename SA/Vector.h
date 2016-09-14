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
	// Contours(윤곽) 필드
	// 벡터 포인트형 벡터(점들이 모여서 선이 되는 원리)
	// 기본 외곽 벡터
	vector<vector<Point>> contours;

	// 손 외곽 벡터
	vector<vector<Point>> handContours;	 

	// 선을 감지하기 위한 벡터
	vector<Vec4i> hierarchy;

	// 움직이기 전 화면 손가락 크기들의 원
	vector<vector<Point>> beforeHandTip;

	// 움직인 후 손가락 크기들 원
	vector<vector<Point>> handTip;

	// 볼록결함 - 움푹 들어간 부분 (ConvexityDefects)

	/*
	*	Vec4i intVecDefects
	*	[0] start_index
	*	[1] end_index
	*	[2] farthest_pt_index
	*	[3] fixpt_depth
	*/
	vector<int> handPointDefects;		 // 움푹 들어간 부분의 벡터
	vector<vector<Point>> pointDefects;  // 점 볼록결함선
	vector<vector<Vec4i>> intVecDefects; // 벡터 볼록결함 감지

	vector<vector<Point>> pointHull;	 // 외곽선
	vector<vector<int>> hullIndexes;     // 외곽선 인덱스
	int contSize = 0; // contours 크기

public:
	Vector();
	void initHandTip();
	void findDrawContours();
	void handRecognization();
	void handTipDetection(KeyBoard&, int i);

	float innerAngle(float, float, float, float, float, float);
	void handTipDetectWithAngle();

	~Vector();
};

#endif // !_VECTOR_H_