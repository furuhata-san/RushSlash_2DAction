#pragma once
#pragma once
#include "AttackArea.h"

class FireAttackArea : public AttackArea {

	int* image;

public:
	FireAttackArea(float posX, float posY, float sizeW, float sizeH, int damage);

	void finalize() override;//�I���E�������
	void update() override;//�X�V����
	void draw() override;//�`�揈��
	void AnimationUpdate();	//�`��X�V
};