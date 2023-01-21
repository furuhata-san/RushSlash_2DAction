#include <Dxlib.h>
#include "../tool/KeyChecker.h"

namespace KeyChecker {

	//�L�[�̏�Ԃ��Ǘ��E�J�E���g����ϐ��i���ڂ̎Q�Ƌ֎~�j
	int KeyState[256] = { 0 };


	//�X�V�����i�Ăяo���̂́A�v���W�F�N�g���ň�񂾂��ɂ��邱�Ɓj
	void GetHitKeyState_UpDate()
	{
		//���ׂẴL�[�̌��݂̏�Ԃ��X�V
		GetHitKeyStateAllEx(KeyState);
	}

	bool InputOn(int KeyCode) {
		//�L�[�������ꂽ���ォ��P�t���[���o�ߌ��true
		if (KeyState[KeyCode] > 1) { 
			return true;
		}

		//����ȊO��false
		return false;
	}

	//�����ꂽ�u�Ԃ̂�true��
	bool InputDown(int KeyCode) {
		//�L�[�������ꂽ�u�Ԃ�true
		if (KeyState[KeyCode] == 1) {
			return true;
		}

		//����ȊO��false
		return false;
	}


	//�����ꂽ�u�Ԃ̂�true��
	bool InputUp(int KeyCode) {
		//�L�[�������ꂽ�u�Ԃ�true
		if (KeyState[KeyCode] == -1) {
			return true;
		}

		//����ȊO��false
		return false;
	}


	//�w�肳�ꂽ�L�[�̌��݂̃J�E���g���擾�iint�^�j
	int	 GetCount(int KeyCode) {
		return KeyState[KeyCode];
	}
}