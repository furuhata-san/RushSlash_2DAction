#pragma once
#include <DxLib.h>

namespace KeyChecker {

	//変数の宣言
	//１＝押された瞬間　−１＝離れた瞬間　それ以上の値　＋−に応じた状態
	extern int KeyState[256];

	//関数の宣言
	extern void GetHitKeyState_UpDate();
	extern bool InputOn(int KeyCode);
	extern bool InputDown(int KeyCode);
	extern bool InputUp(int KeyCode);
	extern int	GetCount(int KeyCode);
}

