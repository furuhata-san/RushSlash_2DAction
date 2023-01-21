#include "Dxlib.h"
#include "../player/Player.h"
#include "../enemy/Enemys.h"
#include "../map/Map.h"
#include "../tool/ViewData.h"	

PurpleEnemy::PurpleEnemy(float x, float y) {
	//�C���[�W���[�h
	this->loadImage(4);

	//���W�ݒ�
	SetPos(x, y);
	SetSize(64, 64);
	//�`����W��ݒ�
	SetSrcPos(0, 0);
	SetSrcSize(32, 32);

	//�ő呬�x�̐ݒ�
	SetMaxSpeed(2, 100);
	moveSpeed = 0.1f;
	SetHitBackSpeed(7.5f);
	ResetNowSpeed();
	SetGravityScale(1);

	//���g�̃^�C�v�ƃq�b�g�^�C�v��ݒ�
	SetMyType(Enemy);
	SetHitType(AttackPlayer);
	//�폜�t���O��false��
	SetRemoveFlag(false);

	//�����̕����͍�
	animAngle = toright;
	moveAngle = moveLeft;

	//��ʊO�̏ꍇ�͈ړ����J�n���Ȃ�
	SetMoveFlag(false);

	//�̗͐ݒ�
	SetLife(40);

	//���G����
	SetIncincible_Bool(false);

	//�����蔻��쐬
	CreateHitBase(GetPosX(), GetPosY(), 50, 50);
}

void PurpleEnemy::EnemyOnlyMove() {

	//���G�Ȃ珈�����s��Ȃ�(�m�b�N�o�b�N��)
	if (GetIncincible_Bool()) return;

	//�߂荞�܂Ȃ��ړ�
	if (animAngle == toleft) {
		AddSpeedX(-moveSpeed, true);
		//�v���C�����E���ɂ����ꍇ�A�����]��
		if (GetPosX() + (GetSizeW() / 2) <= ViewData::GetPlayerWorldPosX()) {
			ResetNowSpeedX();
			animAngle = inleft;
		}
	}
	else if (animAngle == toright) {
		AddSpeedX(moveSpeed, true);
		//�v���C���������ɂ����ꍇ�A�����]��
		if (GetPosX() + (GetSizeW() / 2) >= ViewData::GetPlayerWorldPosX()) {
			ResetNowSpeedX();
			animAngle = inright;
		}
	}

	ObjectMove(GetNowSpeedX(), GetNowSpeedY());
}
