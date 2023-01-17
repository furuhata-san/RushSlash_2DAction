#pragma once
#include "AddList.h"
//typedef std::shared_ptr<Object> Obj;
//typedef std::shared_ptr<HitObjectBase> hObj;

namespace ViewData {


	extern int size_w;	//ウィンドウ横幅
	extern int size_h;	//ウィンドウ縦幅


	extern hObj playerObject;//プレイヤ保存（座標を参照するため）
	extern float playerWorldPosX;
	extern float playerWorldPosY;
	extern void SetPlayerWorldPos(float x, float y);
	extern float GetPlayerWorldPosX();
	extern float GetPlayerWorldPosY();

	extern Obj viewTarget;//描画ターゲット
	extern float renderPosX; //プロジェクト全体の描画座標(X)
	extern float renderPosY; //プロジェクト全体の描画座標(Y)
	extern void SetRenderPos(float x, float y);
	extern float GetRenderPosX();
	extern float GetRenderPosY();
}
