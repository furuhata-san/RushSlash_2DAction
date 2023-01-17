#include "HitObjectBase.h"
#include "ViewData.h"
#include "Map.h"

void HitObjectBase::SetMyType(HitObjectType type) { 
	 myType = type; //���g�̃^�C�v
}

HitObjectBase::HitObjectType HitObjectBase::GetMyType() {
	 return myType; 
}

void HitObjectBase::SetHitType(HitObjectType type) {
	 hitType = type; //�����蔻����s���^�C�v
}

HitObjectBase::HitObjectType HitObjectBase::GetHitType() {
	 return hitType;
}

void HitMove(HitObjectBase& you) {/*Nop*/ };

void HitObjectBase::SetDamage(int value) { 
	 damage = value; 
}

int HitObjectBase::GetDamage() { 
	 return damage;
}

void HitObjectBase::CreateHitBase(float x, float y, float w, float h) {//�����蔻����쐬�i�J�nX���W�A�J�nY���W�A����̕��A����̍����j
 hitX = x;
 hitY = y;
 hitW = w;
 hitH = h;
}

void HitObjectBase::UpdateHitBase(float posX, float posY) {//�����蔻��̍��W�X�V
	hitX = posX;
	hitY = posY;
}

void HitObjectBase::InvincibleInitialize_Time(int time) {
	 invincibleTime = time;
	 invincibleCounter = time; 
}
void HitObjectBase::SetIncincible_Time() { 
	 invincibleCounter = 0;
}

bool HitObjectBase::GetIncincible_Time() { //�����J�E���g�����G���Ԃ𒴂��Ă����疳�G�𖳌���
	++invincibleCounter;
	return invincibleCounter < invincibleTime;
}

int HitObjectBase::GetIncincible_Count() {
	 return invincibleCounter; 
 }

void HitObjectBase::SetIncincible_Bool(bool value) {
	 invincibleFlag = value; 
}

bool HitObjectBase::GetIncincible_Bool() {
	 return invincibleFlag; 
}

float HitObjectBase::GetHitX() { return hitX; }//���̃I�u�W�F�N�g�̓����蔻��iX���W�j
float HitObjectBase::GetHitY() { return hitY; }//���̃I�u�W�F�N�g�̓����蔻��iY���W�j
float HitObjectBase::GetHitW() { return hitW; }//���̃I�u�W�F�N�g�̓����蔻��i�����j
float HitObjectBase::GetHitH() { return hitH; }//���̃I�u�W�F�N�g�̓����蔻��i�c���j

//�U���������i�����鑤�j�����̔�����Ăяo��
bool HitObjectBase::HitJudge(HitObjectBase& you) {
	
	//�����蔻����쐬���A����
	if (this->hitX <= you.hitX + you.hitW) {
		if (this->hitX + this->hitW >= you.hitX) {
			if (this->hitY <= you.hitY + you.hitH) {
				if (this->hitY + this->hitH >= you.hitY) {
					//�����蔻�肪�d�Ȃ��Ă���
					return true;

				}
			}
		}
	}
	//�����蔻��͏d�Ȃ��Ă��Ȃ�
	return false;
}

//�߂荞�܂Ȃ��ړ�
void HitObjectBase::ObjectMove(float preX, float preY) {

	while (preX != 0) {
		int save_x = GetPosX();
		if (preX >= 1) { AddPosX(1); preX -= 1; }
		else if (preX <= -1) { AddPosX(-1); preX += 1; }
		else { AddPosX(preX); preX = 0; }

		//�����蔻��̈ʒu�X�V
		UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2),this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));

		//���肪�q�b�g������
		if (Map::MapCheckHit(GetHitX(), GetHitY(), GetHitW(), GetHitH())) {
			//�ړ��L�����Z��
			SetPos(save_x,GetPosY());
			//���x���Z�b�g
			ResetNowSpeedX();
			//�����蔻��̈ʒu�X�V
			UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
		}
	}

	while (preY != 0) {
		int save_y = GetPosY();
		if (preY >= 1) { AddPosY(1); preY -= 1; }
		else if (preY <= -1) { AddPosY(-1); preY += 1; }
		else { AddPosY(preY); preY = 0; }

		//�����蔻��̈ʒu�X�V
		UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2),this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));

		//���肪�q�b�g������
		if (Map::MapCheckHit(GetHitX(), GetHitY(), GetHitW(), GetHitH())) {
			//�ړ��L�����Z��
			SetPos(GetPosX(), save_y);
			//���x���Z�b�g
			ResetNowSpeedY();
			//�����蔻��̈ʒu�X�V
			UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
		}
	}
}