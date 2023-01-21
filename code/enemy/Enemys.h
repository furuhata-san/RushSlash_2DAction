#pragma once
#include "../enemy/EnemyBase.h"

//�����G�i���ړ��̂݁j
class BlackEnemy : public EnemyBase {

	//���̂Ƃ���Ȃ�

public:
	BlackEnemy(float x, float y);
	//�G�l�~�[���Ƃ̓��L�̓���
	void EnemyOnlyMove() override;

	//�ǉ��������ϐ��͈ȉ���
	float moveSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};


//���G�i�ǂ�o���Ă���G�j
class BlueEnemy : public EnemyBase {

	//���̂Ƃ���Ȃ�

public:
	BlueEnemy(float x, float y);
	//�G�l�~�[���Ƃ̓��L�̓���
	void EnemyOnlyMove() override;

	//�ǉ��������ϐ��͈ȉ���
	float moveSpeed;
	float climeSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};

//�΂̓G�i���˂�G�j
class GreenEnemy : public EnemyBase {

	//���̂Ƃ���Ȃ�

public:
	GreenEnemy(float x, float y);
	//�G�l�~�[���Ƃ̓��L�̓���
	void EnemyOnlyMove() override;

	//�ǉ��������ϐ��͈ȉ���
	float moveSpeed;
	float jumpForce;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};

//���̓G�i�ǂ������Ă���G�j
class PurpleEnemy : public EnemyBase {

	//���̂Ƃ���Ȃ�

public:
	PurpleEnemy(float x, float y);
	//�G�l�~�[���Ƃ̓��L�̓���
	void EnemyOnlyMove() override;

	//�ǉ��������ϐ��͈ȉ���
	float moveSpeed;
	float hitBackSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};


//�Ԃ��G�i�����Ȃ��G�j
class RedEnemy : public EnemyBase {

	//���̂Ƃ���Ȃ�

public:
	RedEnemy(float x, float y);
	//�G�l�~�[���Ƃ̓��L�̓���
	void EnemyOnlyMove() override;


	//�ǉ��������ϐ��͈ȉ���
	float moveSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};