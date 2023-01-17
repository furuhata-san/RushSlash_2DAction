#pragma once
#include "DxLib.h"
#include "Object.h"

class HitObjectBase : public Object {

public:
	enum HitObjectType {
		AllHit,//�������Ȃ��@���ׂẴq�b�g�I�u�W�F�N�g�Ɠ����蔻����s��

		//�ǉ��������ꍇ�͈ȉ�////////////////////////////////////////////////////
		Player,
		Enemy,
		AttackPlayer,
		Item,

		//�����܂�////////////////////////////////////////////////////////////////

		Non//�������Ȃ��@���ׂẴq�b�g�I�u�W�F�N�g�Ɠ����蔻����s��Ȃ�
		//�ȉ��ւ̒ǉ��͋֎~
	};

private:

	//�����蔻��̋��̍��W
	float hitX, hitY;
	float hitW, hitH;
	HitObjectType myType;
	HitObjectType hitType;

	int invincibleCounter;//���ڎQ�Ƌ֎~
	int invincibleTime;//���ڎQ�Ƌ֎~
	bool invincibleFlag;//���ڎQ�Ƌ֎~

	int damage;//���ڎQ�Ƌ֎~

public:

	HitObjectBase() {};

	//���L����֐��݂̂��L�q
	virtual bool HitJudge(HitObjectBase& you);//�w��I�u�W�F�N�g�ƃq�b�g���Ă��邩

	virtual void SetMyType(HitObjectType type);//���g�̃^�C�v
	virtual HitObjectType GetMyType();
	virtual void SetHitType(HitObjectType type);//�����蔻����s���^�C�v
	virtual HitObjectType GetHitType();

	virtual void HitMove(HitObjectBase& you){/*nop*/ };

	virtual void SetDamage(int value);//���̃I�u�W�F�N�g���q�b�g�����I�u�W�F�N�g�ɗ^����_���[�W�ʂ�ݒ�
	virtual int GetDamage();//���̃I�u�W�F�N�g�����_���[�W��߂�l�Ƃ��ē���

	virtual void CreateHitBase(float x, float y, float w, float h);

	virtual void UpdateHitBase(float posX, float posY);

	virtual void ObjectMove(float preX, float preY);//�߂荞�܂Ȃ��ړ�

	//���G��Ԃ̃��Z�b�g
	virtual void InvincibleInitialize_Time(int time);//���G���Ԃ̏����ݒ�
	virtual void SetIncincible_Time();//���G�N��
	virtual bool GetIncincible_Time();//�����J�E���g�����G���Ԃ𒴂��Ă����疳�G�𖳌���

	virtual int GetIncincible_Count();
	virtual void SetIncincible_Bool(bool value);
	virtual bool GetIncincible_Bool();


	virtual float GetHitX();//���̃I�u�W�F�N�g�̓����蔻��iX���W�j
	virtual float GetHitY();//���̃I�u�W�F�N�g�̓����蔻��iY���W�j
	virtual float GetHitW();//���̃I�u�W�F�N�g�̓����蔻��i�����j
	virtual float GetHitH();//���̃I�u�W�F�N�g�̓����蔻��i�c���j
};