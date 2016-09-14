/*
* 키보드
*/
#include "stdafx.h"
#include "KeyBoard.h"


// 생성자
KeyBoard::KeyBoard() : alpha(1.0), beta(0.5) {
	// 윈도우 'INPUT' 이벤트 구조체에서 
	// 키보드 이벤트를 받아온다.
	// Default로 유니코드를 받아온다.
	ip.type = INPUT_KEYBOARD; //키보드 이벤트 셋업
	ip.ki.wScan = 0; // 키 스캔 초기화
	ip.ki.time = 0; // 키를 받는 시간 초기화
	ip.ki.dwExtraInfo = 0; // 추가적으로 받아오는 정보 초기화
}

double KeyBoard::getAlpha()
{
	return alpha;
}

double KeyBoard::getBeta()
{
	return beta;
}

// 키보드 네모형태 설정
void KeyBoard::keyBoardReg(Mat &mat) {
	//Rect name(Xpoint, Ypoint, Width, Height);

	Rect keyBoard(20, 260, 600, 200);
	/*Line5*/
	Rect tilt(20, 260, 40, 40);				//~
	Rect Num1(60, 260, 40, 40);				//1
	Rect Num2(100, 260, 40, 40);			//2
	Rect Num3(140, 260, 40, 40);			//3
	Rect Num4(180, 260, 40, 40);			//4
	Rect Num5(220, 260, 40, 40);			//5
	Rect Num6(260, 260, 40, 40);			//6
	Rect Num7(300, 260, 40, 40);			//7
	Rect Num8(340, 260, 40, 40);			//8
	Rect Num9(380, 260, 40, 40);			//9
	Rect Num0(420, 260, 40, 40);			//0
	Rect minus(460, 260, 40, 40);			//-
	Rect equal(500, 260, 40, 40);			//=
	Rect backSpace(540, 260, 80, 40);		//backspace

											/*Line4*/
	Rect tab(20, 300, 60, 40);				//tab
	Rect alphaQ(80, 300, 40, 40);			//Q
	Rect alphaW(120, 300, 40, 40);			//W
	Rect alphaE(160, 300, 40, 40);			//E
	Rect alphaR(200, 300, 40, 40);			//R
	Rect alphaT(240, 300, 40, 40);			//T
	Rect alphaY(280, 300, 40, 40);			//Y
	Rect alphaU(320, 300, 40, 40);			//U
	Rect alphaI(360, 300, 40, 40);			//I
	Rect alphaO(400, 300, 40, 40);			//O
	Rect alphaP(440, 300, 40, 40);			//P
	Rect braceLeft(480, 300, 40, 40);		//[
	Rect braceRight(520, 300, 40, 40);		//]
	Rect backSlash(560, 300, 60, 40);		//\
																								
/*Line3*/
	Rect capsLock(20, 340, 80, 40);			//capslock
	Rect alphaA(100, 340, 40, 40);			//A
	Rect alphaS(140, 340, 40, 40);			//S
	Rect alphaD(180, 340, 40, 40);			//D
	Rect alphaF(220, 340, 40, 40);			//F
	Rect alphaG(260, 340, 40, 40);			//G
	Rect alphaH(300, 340, 40, 40);			//H
	Rect alphaJ(340, 340, 40, 40);			//J
	Rect alphaK(380, 340, 40, 40);			//K
	Rect alphaL(420, 340, 40, 40);			//L
	Rect colon(460, 340, 40, 40);			//;
	Rect quotation(500, 340, 40, 40);		//'
	Rect enter(540, 340, 80, 40);			//enter

											/*Line2*/
	Rect shiftLeft(20, 380, 100, 40);		//left shift
	Rect alphaZ(120, 380, 40, 40);			//Z
	Rect alphaX(160, 380, 40, 40);			//X
	Rect alphaC(200, 380, 40, 40);			//C
	Rect alphaV(240, 380, 40, 40);			//V
	Rect alphaB(280, 380, 40, 40);			//B
	Rect alphaN(320, 380, 40, 40);			//N
	Rect alphaM(360, 380, 40, 40);			//M
	Rect bracketsLeft(400, 380, 40, 40);	//<	
	Rect bracketsRight(440, 380, 40, 40);	//>
	Rect question(480, 380, 40, 40);		//?
	Rect shiftRight(520, 380, 100, 40);		//right shift

											/*Line1*/
	Rect ctrlLeft(20, 420, 60, 40);			//left ctrl
	Rect winLeft(80, 420, 60, 40);			//left win
	Rect altLeft(140, 420, 60, 40);			//left alt
	Rect spaceBar(200, 420, 180, 40);		//spacebar
	Rect convertLanguage(380, 420, 60, 40);	//Kor/Eng
	Rect altRight(440, 420, 60, 40);		//right alt
	Rect winRight(500, 420, 60, 40);		//right win
	Rect ctrlRight(560, 420, 60, 40);		//right ctrl


											/*Make rectangle to mat.*/
	rectangle(mat, keyBoard, Scalar(255, 0, 0));

	rectangle(mat, tilt, Scalar(255, 0, 0));
	rectangle(mat, Num1, Scalar(255, 0, 0));
	rectangle(mat, Num2, Scalar(255, 0, 0));
	rectangle(mat, Num3, Scalar(255, 0, 0));
	rectangle(mat, Num4, Scalar(255, 0, 0));
	rectangle(mat, Num5, Scalar(255, 0, 0));
	rectangle(mat, Num6, Scalar(255, 0, 0));
	rectangle(mat, Num7, Scalar(255, 0, 0));
	rectangle(mat, Num8, Scalar(255, 0, 0));
	rectangle(mat, Num9, Scalar(255, 0, 0));
	rectangle(mat, Num0, Scalar(255, 0, 0));
	rectangle(mat, minus, Scalar(255, 0, 0));
	rectangle(mat, equal, Scalar(255, 0, 0));
	rectangle(mat, backSpace, Scalar(255, 0, 0));

	rectangle(mat, tab, Scalar(255, 0, 0));
	rectangle(mat, alphaQ, Scalar(255, 0, 0));
	rectangle(mat, alphaW, Scalar(255, 0, 0));
	rectangle(mat, alphaE, Scalar(255, 0, 0));
	rectangle(mat, alphaR, Scalar(255, 0, 0));
	rectangle(mat, alphaT, Scalar(255, 0, 0));
	rectangle(mat, alphaY, Scalar(255, 0, 0));
	rectangle(mat, alphaU, Scalar(255, 0, 0));
	rectangle(mat, alphaI, Scalar(255, 0, 0));
	rectangle(mat, alphaO, Scalar(255, 0, 0));
	rectangle(mat, alphaP, Scalar(255, 0, 0));
	rectangle(mat, braceLeft, Scalar(255, 0, 0));
	rectangle(mat, braceRight, Scalar(255, 0, 0));
	rectangle(mat, backSlash, Scalar(255, 0, 0));

	rectangle(mat, capsLock, Scalar(255, 0, 0));
	rectangle(mat, alphaA, Scalar(255, 0, 0));
	rectangle(mat, alphaS, Scalar(255, 0, 0));
	rectangle(mat, alphaD, Scalar(255, 0, 0));
	rectangle(mat, alphaF, Scalar(255, 0, 0));
	rectangle(mat, alphaG, Scalar(255, 0, 0));
	rectangle(mat, alphaH, Scalar(255, 0, 0));
	rectangle(mat, alphaJ, Scalar(255, 0, 0));
	rectangle(mat, alphaK, Scalar(255, 0, 0));
	rectangle(mat, alphaL, Scalar(255, 0, 0));
	rectangle(mat, colon, Scalar(255, 0, 0));
	rectangle(mat, quotation, Scalar(255, 0, 0));
	rectangle(mat, enter, Scalar(255, 0, 0));

	rectangle(mat, shiftLeft, Scalar(255, 0, 0));
	rectangle(mat, alphaZ, Scalar(255, 0, 0));
	rectangle(mat, alphaX, Scalar(255, 0, 0));
	rectangle(mat, alphaC, Scalar(255, 0, 0));
	rectangle(mat, alphaV, Scalar(255, 0, 0));
	rectangle(mat, alphaB, Scalar(255, 0, 0));
	rectangle(mat, alphaN, Scalar(255, 0, 0));
	rectangle(mat, alphaM, Scalar(255, 0, 0));
	rectangle(mat, bracketsLeft, Scalar(255, 0, 0));
	rectangle(mat, bracketsRight, Scalar(255, 0, 0));
	rectangle(mat, question, Scalar(255, 0, 0));
	rectangle(mat, shiftRight, Scalar(255, 0, 0));

	rectangle(mat, ctrlLeft, Scalar(255, 0, 0));
	rectangle(mat, winLeft, Scalar(255, 0, 0));
	rectangle(mat, altLeft, Scalar(255, 0, 0));
	rectangle(mat, spaceBar, Scalar(255, 0, 0));
	rectangle(mat, convertLanguage, Scalar(255, 0, 0));
	rectangle(mat, altRight, Scalar(255, 0, 0));
	rectangle(mat, winRight, Scalar(255, 0, 0));
	rectangle(mat, ctrlRight, Scalar(255, 0, 0));

}

void KeyBoard::keyBoardInput(int x, int y) {

	if (y > 420 && y < 460) {	// 420 < y < 460 , Line1
		if (x > 20 && x < 80) {
			//ctrl left

			ip.ki.wVk = VK_LCONTROL;//0xA2 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
//		else if (x > 80 && x < 140) {	// in left windows button.
//										//win left
//			ip.ki.wVk = VK_LWIN; //0x5B // virtual-key code for the key value
//			ip.ki.dwFlags = 0; // 0 for key press
//			SendInput(1, &ip, sizeof(INPUT));
//
//			// Release the key value
//			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
//			SendInput(1, &ip, sizeof(INPUT));
//		}
		else if (x > 140 && x < 200) {
			//alt left
			ip.ki.wVk = VK_LMENU;	//0xA4 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 200 && x < 380) {
			//space bar
			ip.ki.wVk = VK_SPACE;// 0x20 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 380 && x < 440) {
			//convertLanguage
			ip.ki.wVk = VK_HANGUL;// 0x15 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 440 && x < 500) {
			//alt Right
			ip.ki.wVk = VK_RMENU;	//0xA5 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
//		else if (x > 500 && x < 560) {
//			//win right
//			ip.ki.wVk = VK_RWIN;// 0x5C // virtual-key code for the key value
//			ip.ki.dwFlags = 0; // 0 for key press
//			SendInput(1, &ip, sizeof(INPUT));
//
//			// Release the key value
//			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
//			SendInput(1, &ip, sizeof(INPUT));
//		}
		else if (x > 560 && x < 620) {
			//ctrl right
			ip.ki.wVk = VK_RCONTROL;//0xA3 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		//	else {

		//	}
	}
	else if (y > 380 && y < 420) {		// 380 < y < 420 line 2
		if (x > 20 && x < 120) {
			//shift left
			ip.ki.wVk = VK_LSHIFT;// 0xA0 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 120 && x < 160) {	// in left windows button.
										//alphabet z
			ip.ki.wVk = 0x5A; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 160 && x < 200) {
			//alphabet x
			ip.ki.wVk = 0x58;// virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 200 && x < 240) {
			//c
			ip.ki.wVk = 0x43; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 240 && x < 280) {
			//v
			ip.ki.wVk = 0x56; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 280 && x < 320) {
			//b
			ip.ki.wVk = 0x42; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 320 && x < 360) {
			//n
			ip.ki.wVk = 0x4E; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 360 && x < 400) {
			//m
			ip.ki.wVk = 0x4D; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 400 && x < 440) {
			// comma
			ip.ki.wVk = VK_OEM_COMMA; //0xBC;// virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 440 && x < 480) {
			// period point
			ip.ki.wVk = VK_OEM_PERIOD; //0xBE; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 480 && x < 520) {
			// slash
			ip.ki.wVk = VK_OEM_2; //0xBF; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 520 && x < 620) {
			// shift right 
			ip.ki.wVk = VK_RSHIFT;	// 0xA1 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		//	else {

		//	}
	}
	else if (y > 340 && y < 380) {	// 340 < y < 380		line 3
		if (x > 20 && x < 100) {
			//caps lock
			ip.ki.wVk = VK_CAPITAL;// 0x14 // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 100 && x < 140) {	// in left windows button.
										//alphabet a
			ip.ki.wVk = 0x41; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 140 && x < 180) {
			//alphabet s
			ip.ki.wVk = 0x53; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 180 && x < 220) {
			//d
			ip.ki.wVk = 0x44; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 220 && x < 260) {
			//f
			ip.ki.wVk = 0x46; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 260 && x < 300) {
			//g
			ip.ki.wVk = 0x47; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 300 && x < 340) {
			//h
			ip.ki.wVk = 0x48; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 340 && x < 380) {
			//j
			ip.ki.wVk = 0x4a; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 380 && x < 420) {
			//k
			ip.ki.wVk = 0x4B; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 420 && x < 460) {
			//l
			ip.ki.wVk = 0x4C; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 460 && x < 500) {
			// semi colon
			ip.ki.wVk = VK_OEM_1; //0xBA; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 500 && x < 540) {
			// curtation.
			ip.ki.wVk = VK_OEM_7;	//0xDE // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 540 && x < 620) {
			//enter
			ip.ki.wVk = VK_RETURN;// 0x0D // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		//	else {

		//	}
	}
	else if (y > 300 && y < 340) {	// 300 < y < 340				line 4
		if (x > 20 && x < 80) {
			//tab
			ip.ki.wVk = VK_TAB;// 0x09; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 80 && x < 120) {	// in left windows button.
										//alphabet q
			ip.ki.wVk = 0x51; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 120 && x < 160) {
			//alphabet w
			ip.ki.wVk = 0x57; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 160 && x < 200) {
			//e
			ip.ki.wVk = 0x45; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 200 && x < 240) {
			//r
			ip.ki.wVk = 0x52; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 240 && x < 280) {
			//t
			ip.ki.wVk = 0x54;  // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 280 && x < 320) {
			//y
			ip.ki.wVk = 0x59; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 320 && x < 360) {
			//u
			ip.ki.wVk = 0x55; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 360 && x < 400) {
			//i
			ip.ki.wVk = 0x49; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 400 && x < 440) {
			//o
			ip.ki.wVk = 0x4F; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 440 && x < 480) {
			//p
			ip.ki.wVk = 0x50; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 480 && x < 520) {
			//[
			ip.ki.wVk = VK_OEM_4; //0xDB // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 520 && x < 560) {
			// ].
			ip.ki.wVk = VK_OEM_6; // 0xDD // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 560 && x < 620) {
			//back slash
			ip.ki.wVk = VK_OEM_5; // 0xDC // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		//		else {

		//		}
	}
	else if (y > 260 && y < 300) {	// 260 < y < 300		line 1
		if (x > 20 && x < 60) {
			//`
			ip.ki.wVk = VK_OEM_3; //0xC0; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 60 && x < 100) {	// in left windows button.
										//1
			ip.ki.wVk = 0x31; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 100 && x < 140) {
			//2
			ip.ki.wVk = 0x32; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 140 && x < 180) {
			//3
			ip.ki.wVk = 0x33; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 180 && x < 220) {
			//4
			ip.ki.wVk = 0x34; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 220 && x < 260) {
			//5
			ip.ki.wVk = 0x35; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 260 && x < 300) {
			//6
			ip.ki.wVk = 0x36; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 300 && x < 340) {
			//7
			ip.ki.wVk = 0x37; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 340 && x < 380) {
			//8
			ip.ki.wVk = 0x38; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 380 && x < 420) {
			//9
			ip.ki.wVk = 0x39; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 420 && x < 460) {
			//0
			ip.ki.wVk = 0x30; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 460 && x < 500) {
			//-
			ip.ki.wVk = VK_OEM_MINUS; //0x2D;// virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 500 && x < 540) {
			// =
			ip.ki.wVk = VK_OEM_PLUS; //0xBB;	// =	// virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		else if (x > 540 && x < 620) {
			//back space
			ip.ki.wVk = VK_BACK; // 0x08; // virtual-key code for the key value
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			// Release the key value
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}
		//	else {

		//	}
	}
}

// 소멸자
KeyBoard::~KeyBoard() {}