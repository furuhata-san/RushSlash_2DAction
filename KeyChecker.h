#pragma once
#include <DxLib.h>

namespace KeyChecker {

	//�ϐ��̐錾
	//�P�������ꂽ�u�ԁ@�|�P�����ꂽ�u�ԁ@����ȏ�̒l�@�{�|�ɉ��������
	extern int KeyState[256];

	//�֐��̐錾
	extern void GetHitKeyState_UpDate();
	extern bool InputOn(int KeyCode);
	extern bool InputDown(int KeyCode);
	extern bool InputUp(int KeyCode);
	extern int	GetCount(int KeyCode);
}

