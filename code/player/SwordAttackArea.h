#pragma once
#include "AttackArea.h"

class SwordAttackArea : public AttackArea {

	int* image;
	int animNum;	//���ݕ\�����Ă���C���[�W�ԍ�
	int animCount;	//�`�掞�A�j���[�V�����J�E���g
	int animLimit;

public:
	SwordAttackArea(float posX, float posY, float sizeW, float sizeH, int damage);

	void finalize() override;//�I���E�������
	void update() override;//�X�V����
	void draw() override;//�`�揈��
	void AnimationUpdate();	//�`��X�V
};