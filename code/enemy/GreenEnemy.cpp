#include "Dxlib.h"
#include "../player/Player.h"
#include "../enemy/Enemys.h"
#include "../map/Map.h"

GreenEnemy::GreenEnemy(float x, float y) {
	//�C���[�W���[�h
	this->loadImage(3);

	//���W�ݒ�
	SetPos(x, y);
	SetSize(64, 64);
	//�`����W��ݒ�
	SetSrcPos(0, 0);
	SetSrcSize(32, 32);

	//�ő呬�x�̐ݒ�
	SetMaxSpeed(2, 100);
	moveSpeed = 0.1f;
	jumpForce = 7.5f;
	SetHitBackSpeed(7.5f);
	ResetNowSpeed();
	SetGravityScale(0.5f);

	//���g�̃^�C�v�ƃq�b�g�^�C�v��ݒ�
	SetMyType(Enemy);
	SetHitType(AttackPlayer);
	//�폜�t���O��false��
	SetRemoveFlag(false);

	//�����̕����͍�
	animAngle = toleft;
	moveAngle = moveLeft;

	//��ʊO�̏ꍇ�͈ړ����J�n���Ȃ�
	SetMoveFlag(false);

	//�̗͐ݒ�
	SetLife(30);

	//���G����
	SetIncincible_Bool(false);

	//�����蔻��쐬
	CreateHitBase(GetPosX(), GetPosY(), 50, 50);
}

void GreenEnemy::EnemyOnlyMove() {

	//���G�Ȃ珈�����s��Ȃ�(�m�b�N�o�b�N��)
	if (GetIncincible_Bool()) return;

	//�߂荞�܂Ȃ��ړ�
	if (animAngle == toleft) {
		AddSpeedX(-moveSpeed, true);
		//�ǂɂԂ���@�ŕ����]��
		if (Map::MapCheckHit(GetHitX() - 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inleft;
		}
	}
	else if (animAngle == toright) {
		AddSpeedX(moveSpeed, true);
		//�ǂɂԂ���@�ŕ����]��
		if (Map::MapCheckHit(GetHitX() + GetHitW() + 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inright;
		}
	}

	//���n������W�����v�i�҂��҂�񒵂˂�j
	if (Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
		//��xY�������̃X�s�[�h�����Z�b�g���Ă���W�����v
		ResetNowSpeedY();
		AddSpeedY(-jumpForce, true);
	}

	ObjectMove(GetNowSpeedX(), GetNowSpeedY());
}
