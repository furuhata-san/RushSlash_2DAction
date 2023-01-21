#pragma once
#include "../base/HitObjectBase.h"

class AttackArea : public HitObjectBase {

private:

	int attackStartFlame;
	int attackEndFlame;
	int nowCount;

public:

	virtual void SettingAttackFlame(int start, int end) {
		attackStartFlame = start;
		attackEndFlame = end;
	}
	virtual int GetAtteckStertFlame() { return  attackStartFlame; }
	virtual int GetAtteckEndFlame() { return  attackEndFlame; }

	virtual void ResetNowCount() { nowCount = 0; }
	virtual void nowCountUp() { ++nowCount; }
	virtual int GetNowCount() { return nowCount; }
	
	virtual bool JudgeAttackStert() { return nowCount >= attackStartFlame; }
	virtual bool JudgeAttackEnd() { return nowCount >= attackEndFlame; }

	//�A�j���[�V�����֌W
	int animNum;	//���ݕ\�����Ă���C���[�W�ԍ�
	int animCount;	//�`�掞�A�j���[�V�����J�E���g
	int animLimit;
	virtual void AnimationUpdate(){};
};