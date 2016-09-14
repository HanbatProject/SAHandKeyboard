/*
* 키보드 헤더
*/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "stdafx.h"


class KeyBoard {
private:
	INPUT ip;

	// 키보드 투명도 필드
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