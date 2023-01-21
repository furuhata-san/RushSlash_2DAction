#pragma once
#include "../base/HitObjectBase.h"
#include "../scene/AddList.h"

class Player : public HitObjectBase {

	int* image;
	int animNum;
	int animCount;
	int saveHitW, saveHitH;
	int magicChargeValue;
	bool GameResultFlag;

public:
	
	Player(float posX, float posY);//�R���X�g���N�^
	void finalize() override;//�I���E�������
	void update() override;//�X�V����
	void draw() override;//�`�揈��
	void HitMove(HitObjectBase& you) override;		//�q�b�g�����ꍇ�̏���

	//�ǉ�����ϐ��͈ȉ���
	
	//�A�j���[�V����
	enum Motion {
		idle,
		sword,
		magic,
		win,
		run,
		jump,
		damage,
		die
	};
	Motion motion;

	void animMotionUpdate();
	void animCounterReset() { animCount = 0; animNum = 0; }
	int GetAnimNum() { return animNum; }
	bool imageNullChecker(int num) { return num <= (int)Motion::run; }

	//�ړ�
	enum Angle {
		left,
		right
	};
	Angle angle;
	float runForce;
	float jumpForce;

	//�̗�
	int hp;
	int hpMax;

	//����ύX
	void MotionUpdate(Motion& nowMotion);
	void PlayMotion(Motion nowMotion);
	void PlayerFallHole();
	void PlayerGameClear();
	Motion MotionChange(const Motion nowMotion, bool action);

	void DrawLifeGaugeUI();

	void CraeteAttackArea(hObj& hobj);
};