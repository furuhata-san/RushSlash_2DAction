#include <DxLib.h>
#include "ViewData.h"

namespace ViewData {

	//ウィンドウサイズを設定
	int size_w = 1280;
	int size_h = 960;

	//プレイヤがゲーム世界の中心の影武者的存在になる
	//プレイヤのオブジェクト（座標を参照するため）
	hObj playerObject;
	float playerWorldPosX;
	float playerWorldPosY;
	void SetPlayerWorldPos(float x, float y) { playerWorldPosX = x, playerWorldPosY = y; }
	float GetPlayerWorldPosX() { return playerWorldPosX; }
	float GetPlayerWorldPosY() { return playerWorldPosY; }

	//ゲーム全体の描画を行う上での
	//世界の中心となるオブジェクト
	Obj viewTarget;
	float renderPosX = 0;
	float renderPosY = 0;
	void SetRenderPos(float x, float y) { renderPosX = x, renderPosY = y; }
	float GetRenderPosX() { return renderPosX; }
	float GetRenderPosY() { return renderPosY; }
}