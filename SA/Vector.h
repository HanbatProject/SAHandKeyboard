/*
* ���� ���
*/
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "stdafx.h"
#include "TemplateSingleton.h"

class Vector : public TemplateSingleton<Vector> {
private:
	const int DEFECTS_COUNT = 8;
	const int CONTOUR_AREA_MIN = 4000;
	// Contours(����) �ʵ�
	// ���� ����Ʈ�� ����(������ �𿩼� ���� �Ǵ� ����)
	// �⺻ �ܰ� ����
	vector<vector<Point>> contours;

	// �� �ܰ� ����
	vector<vector<Point>> handContours;	 

	// ���� �����ϱ� ���� ����
	vector<Vec4i> hierarchy;

	// �����̱� �� ȭ�� �հ��� ũ����� ��
	vector<vector<Point>> beforeHandTip;

	// ������ �� �հ��� ũ��� ��
	vector<vector<Point>> handTip;

	// ���ϰ��� - ��ǫ �� �κ� (ConvexityDefects)

	/*
	*	Vec4i vecDefects
	*	[0] start_index
	*	[1] end_index
	*	[2] farthest_pt_index
	*	[3] fixpt_depth
	*/
	vector<vector<Point>> pointDefects;  // ���ϰ��� ������ �� ����
	vector<vector<Vec4i>> vecDefects;	 // ���ϰ��� ���͸� �����ϴ� �� ����
	vector<int> handPointDefects;		 // ��ǫ �� �κ��� ���� ������ ����

	vector<vector<Point>> pointHull;	 // �ܰ���
	vector<vector<int>> hullIndexes;     // �ܰ��� �ε���
	int contSize = 0; // contours ũ��

public:
	Vector();
	void initHandTip();
	void findDrawContours();
	void handRecognization();
	void handTipDetection(int i);

	float innerAngle(float, float, float, float, float, float);
	void handTipDetectWithAngle();

	~Vector();
};

#endif // !_VECTOR_H_