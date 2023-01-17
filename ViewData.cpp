#include <DxLib.h>
#include "ViewData.h"

namespace ViewData {

	//�E�B���h�E�T�C�Y��ݒ�
	int size_w = 1280;
	int size_h = 960;

	//�v���C�����Q�[�����E�̒��S�̉e���ғI���݂ɂȂ�
	//�v���C���̃I�u�W�F�N�g�i���W���Q�Ƃ��邽�߁j
	hObj playerObject;
	float playerWorldPosX;
	float playerWorldPosY;
	void SetPlayerWorldPos(float x, float y) { playerWorldPosX = x, playerWorldPosY = y; }
	float GetPlayerWorldPosX() { return playerWorldPosX; }
	float GetPlayerWorldPosY() { return playerWorldPosY; }

	//�Q�[���S�̂̕`����s����ł�
	//���E�̒��S�ƂȂ�I�u�W�F�N�g
	Obj viewTarget;
	float renderPosX = 0;
	float renderPosY = 0;
	void SetRenderPos(float x, float y) { renderPosX = x, renderPosY = y; }
	float GetRenderPosX() { return renderPosX; }
	float GetRenderPosY() { return renderPosY; }
}