/*
* Ű���� ���
*/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "stdafx.h"


class KeyBoard {
private:
	INPUT ip;

	// Ű���� ���� �ʵ�
	double alpha, beta;
public:
	KeyBoard();
	void keyBoardReg(Mat &mat);
	void keyBoardInput(int x, int y);

	// getters
	double getAlpha();
	double getBeta();

	~KeyBoard();
};

#endif // !_KEYBOARD_H_