#include "../object/Camera.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/KeyChecker.h"
#include "../scene/GameMgr.h"
#include "../player/Player.h"

Camera::Camera() {

	//最初は向きなし
	angle = non;

	posDistanceX = 150;
	posDistanceY = 300;
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
	float moveXValue = ViewData::playerWorldPosX - GetPosX();
	if (angle == Angle::left) {
		moveXValue -= posDistanceX;
	}
	else if (angle == Angle::right) {
		moveXValue += posDistanceX;
	}

	float moveYValue = (ViewData::playerWorldPosY - posDistanceY) - GetPosY();

	//クリア時もにはカメラを動かせないように
	if (!Game::clearJudge()) {
		AddPosX(moveXValue * moveValue);
		AddPosY(moveYValue * moveValue);
	}

}

void Camera::draw() {
	//nop
}