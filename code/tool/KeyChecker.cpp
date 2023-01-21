#include <Dxlib.h>
#include "../tool/KeyChecker.h"

namespace KeyChecker {

	//キーの状態を管理・カウントする変数（直接の参照禁止）
	int KeyState[256] = { 0 };


	//更新処理（呼び出すのは、プロジェクト内で一回だけにすること）
	void GetHitKeyState_UpDate()
	{
		//すべてのキーの現在の状態を更新
		GetHitKeyStateAllEx(KeyState);
	}

	bool InputOn(int KeyCode) {
		//キーが押された直後から１フレーム経過後はtrue
		if (KeyState[KeyCode] > 1) { 
			return true;
		}

		//それ以外はfalse
		return false;
	}

	//押された瞬間のみtrueに
	bool InputDown(int KeyCode) {
		//キーが押された瞬間はtrue
		if (KeyState[KeyCode] == 1) {
			return true;
		}

		//それ以外はfalse
		return false;
	}


	//離された瞬間のみtrueに
	bool InputUp(int KeyCode) {
		//キーが離された瞬間はtrue
		if (KeyState[KeyCode] == -1) {
			return true;
		}

		//それ以外はfalse
		return false;
	}


	//指定されたキーの現在のカウントを取得（int型）
	int	 GetCount(int KeyCode) {
		return KeyState[KeyCode];
	}
}