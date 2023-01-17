#pragma once
#include <DxLib.h>

namespace KeyChecker {

	//•Ï”‚ÌéŒ¾
	//‚P‰Ÿ‚³‚ê‚½uŠÔ@|‚P—£‚ê‚½uŠÔ@‚»‚êˆÈã‚Ì’l@{|‚É‰‚¶‚½ó‘Ô
	extern int KeyState[256];

	//ŠÖ”‚ÌéŒ¾
	extern void GetHitKeyState_UpDate();
	extern bool InputOn(int KeyCode);
	extern bool InputDown(int KeyCode);
	extern bool InputUp(int KeyCode);
	extern int	GetCount(int KeyCode);
}

