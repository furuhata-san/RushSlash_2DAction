#pragma once
#include "../base/Object.h"
#include "../scene/AddList.h"

//�G�t�F�N�g�����p�֐�
extern void CreateEffect(const Obj& obj);

//�I�u�W�F�N�g�p���G�t�F�N�g�N���X(�C�����C���֐�)
class Effect : public Object {

	int* image;
	float speed;
	float counter;
	bool drawFlag;
	bool UIMode;

	int imageCutTotalNum;
	int imageTurnNum;


public:

	enum AnimMode {
		normal,
		flashing,
		animationLoop,
		animationOnce,
	};
	AnimMode nowMode;

	Effect(
		int* imageAddress,
		float x,
		float y,
		float w,
		float h,
		float dx,
		float dy,
		float dw,
		float dh,
		AnimMode animMode,
		bool UI_Mode,
		bool firstDrawing = true,
		float playSpeed = 0,
		int cutTotal = 0, 
		int turnNum = 0
	);

	virtual void finalize();//�I���E�������
	virtual void update();//�X�V����
	virtual void draw();//�`�揈��

};
