#pragma once
#include "Dxlib.h"
#include "HitObjectBase.h"
#include "DataLoader.h"
#include "ViewData.h"

class EnemyBase : public HitObjectBase {

	int* image;
	int animNum;
	int animCount;
	int enemyType;
	int angleMoveNum;

	int life;
	int lifeMax;

	bool moveFlag;//�������ǂ���

	float hitBackSpeed;
	float gravityScale;

public:

	//�C���[�W�ǂݍ���
	void loadImage(int EnemyType) { image = &Loader::EnemysImg[EnemyType]; };

	//�q�b�g�����ꍇ�̏���
	void SetHitBackSpeed(float speed) { hitBackSpeed = speed; }
	void HitMove(HitObjectBase& you);

	void SetMoveFlag(bool value) { moveFlag = value; }
	bool GetMoveFlag() { return moveFlag; }
	void EnemyOnScreen();

	void finalize() override;//�I���E�������
	void update() override;//�X�V����
	void draw() override;//�`�揈��

	//�G�l�~�[���Ƃ̌ŗL�̓���
	virtual void EnemyOnlyMove(){/*Nop*/};

	//�ǉ�����ϐ��͈ȉ���
	void SetLife(int value) { lifeMax = value;  life = value; }
	void AddLife(int value) { life += value; }
	int GetLife() { return life; }
	bool LifeIsZero() { return life <= 0; }
	void SetGravityScale(float value) { gravityScale = value; };

	//�A�j���[�V����
	enum AnimAngle {
		tofront,
		toleft,
		toright,
		toback,
		inleft,
		inright,
		outleft,
		outright,

		Non
	};
	AnimAngle animAngle;
	AnimAngle saveAnimAngle;
	void animMotionUpdate();
	void animCounterReset() { animCount = 0; animNum = 0; }
	int GetAnimNum() { return animNum; }
	void FallHoleRemove();
	void CreateDieEffect();
};