#include "../object/Camera.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/KeyChecker.h"
#include "../scene/GameMgr.h"

Camera::Camera() {

	//最初は向きなし
	angle = non;

	posDistance = 150;
	moveValue = 0.05f;

	SetPos(0,0);
	SetRemoveFlag(false);
}

void Camera::finalize() {
	//座標リセット
	ViewData::playerWorldPosX = 0;
	ViewData::playerWorldPosY = 0;
	ViewData::renderPosX = 0;
	ViewData::renderPosY = 0;
}

void Camera::update() {
	//向き判断
	if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
		angle = Angle::left;
	}
	else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
		angle = Angle::right;
	}

	//ターゲットの位置へ徐々に移動
	//X移動のみ計算を行う(仮)
	float moveXValue = ViewData::playerWorldPosX - GetPosX();
	if (angle == Angle::left) {
		moveXValue -= posDistance;
	}
	else if (angle == Angle::right) {
		moveXValue += posDistance;
	}

	//クリア時はカメラを動かせない
	//ゲームオーバー時は見渡せるようにする
	if (!Game::clearJudge()) {
		AddPosX(moveXValue * moveValue);
	}

}

void Camera::draw() {
	//nop
}