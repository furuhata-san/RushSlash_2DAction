#include "Dxlib.h"
#include "Player.h"
#include "Enemys.h"
#include "Map.h"

BlackEnemy::BlackEnemy(float x, float y) {
	//�C���[�W���[�h
	this->loadImage(0);

	//���W�ݒ�
	SetPos(x, y);
	SetSize(64, 64);
	//�`����W��ݒ�
	SetSrcPos(0, 0);
	SetSrcSize(32, 32);

	//�ő呬�x�̐ݒ�
	SetMaxSpeed(1, 100);
	moveSpeed = 0.1f;
	SetHitBackSpeed(7.5f);
	ResetNowSpeed();
	SetGravityScale(0.8f);

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
	SetLife(60);

	//���G����
	SetIncincible_Bool(false);

	//�����蔻��쐬
	CreateHitBase(GetPosX(), GetPosY(), 50, 50);
}

void BlackEnemy::EnemyOnlyMove() {

	//���G�Ȃ珈�����s��Ȃ�(�m�b�N�o�b�N��)
	if (GetIncincible_Bool()) return;

	//�߂荞�܂Ȃ��ړ�
	if (animAngle == toleft) {
		AddSpeedX(-moveSpeed, true);
		//�ǂɂԂ���ƕ����]��
		if (Map::MapCheckHit(GetHitX() - 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inleft;
		}
	}
	else if (animAngle == toright) {
		AddSpeedX(moveSpeed, true);
		//�ǂɂԂ���ƕ����]��
		if (Map::MapCheckHit(GetHitX() + GetHitW() + 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inright;
		}
	}

	ObjectMove(GetNowSpeedX(), GetNowSpeedY());
}