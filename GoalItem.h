#pragma once
#include "HitObjectBase.h"

class GoalItem : public HitObjectBase {

	int* image;

public:

	GoalItem(float x, float y, int colerNum);

	void finalize() override;//�I���E�������
	void update() override;//�X�V����
	void draw() override;//�`�揈��
	void HitMove(HitObjectBase& you) override;		//�q�b�g�����ꍇ�̏���
};