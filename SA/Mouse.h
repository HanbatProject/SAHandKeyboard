/*
* 마우스 헤더
*/
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "stdafx.h"

class Mouse {
public:
	Mouse();
	static void onMouse(int event, int x, int y, int flag, void* param);
	~Mouse();
};

#endif // !_MOUSE_H_