#pragma once
#include "AddList.h"
//typedef std::shared_ptr<Object> Obj;
//typedef std::shared_ptr<HitObjectBase> hObj;

namespace ViewData {


	extern int size_w;	//�E�B���h�E����
	extern int size_h;	//�E�B���h�E�c��


	extern hObj playerObject;//�v���C���ۑ��i���W���Q�Ƃ��邽�߁j
	extern float playerWorldPosX;
	extern float playerWorldPosY;
	extern void SetPlayerWorldPos(float x, float y);
	extern float GetPlayerWorldPosX();
	extern float GetPlayerWorldPosY();

	extern Obj viewTarget;//�`��^�[�Q�b�g
	extern float renderPosX; //�v���W�F�N�g�S�̂̕`����W(X)
	extern float renderPosY; //�v���W�F�N�g�S�̂̕`����W(Y)
	extern void SetRenderPos(float x, float y);
	extern float GetRenderPosX();
	extern float GetRenderPosY();
}