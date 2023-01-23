#include "../object/Camera.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/KeyChecker.h"
#include "../scene/GameMgr.h"
#include "../player/Player.h"

Camera::Camera() {

	//�ŏ��͌����Ȃ�
	angle = non;

	posDistanceX = 150;
	posDistanceY = 300;
	moveValue = 0.05f;

	SetPos(0,0);
	SetRemoveFlag(false);
}

void Camera::finalize() {
	//���W���Z�b�g
	ViewData::playerWorldPosX = 0;
	ViewData::playerWorldPosY = 0;
	ViewData::renderPosX = 0;
	ViewData::renderPosY = 0;
}

void Camera::update() {

	//�������f
	if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
		angle = Angle::left;
	}
	else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
		angle = Angle::right;
	}

	//�^�[�Q�b�g�̈ʒu�֏��X�Ɉړ�
	float moveXValue = ViewData::playerWorldPosX - GetPosX();
	if (angle == Angle::left) {
		moveXValue -= posDistanceX;
	}
	else if (angle == Angle::right) {
		moveXValue += posDistanceX;
	}

	float moveYValue = (ViewData::playerWorldPosY - posDistanceY) - GetPosY();

	//�N���A�����ɂ̓J�����𓮂����Ȃ��悤��
	if (!Game::clearJudge()) {
		AddPosX(moveXValue * moveValue);
		AddPosY(moveYValue * moveValue);
	}

}

void Camera::draw() {
	//nop
}