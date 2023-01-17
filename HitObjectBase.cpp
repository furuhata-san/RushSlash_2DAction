#include "HitObjectBase.h"
#include "ViewData.h"
#include "Map.h"

void HitObjectBase::SetMyType(HitObjectType type) { 
	 myType = type; //自身のタイプ
}

HitObjectBase::HitObjectType HitObjectBase::GetMyType() {
	 return myType; 
}

void HitObjectBase::SetHitType(HitObjectType type) {
	 hitType = type; //当たり判定を行うタイプ
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

void HitObjectBase::CreateHitBase(float x, float y, float w, float h) {//当たり判定を作成（開始X座標、開始Y座標、判定の幅、判定の高さ）
 hitX = x;
 hitY = y;
 hitW = w;
 hitH = h;
}

void HitObjectBase::UpdateHitBase(float posX, float posY) {//当たり判定の座標更新
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

bool HitObjectBase::GetIncincible_Time() { //内部カウントが無敵時間を超えていたら無敵を無効化
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

float HitObjectBase::GetHitX() { return hitX; }//このオブジェクトの当たり判定（X座標）
float HitObjectBase::GetHitY() { return hitY; }//このオブジェクトの当たり判定（Y座標）
float HitObjectBase::GetHitW() { return hitW; }//このオブジェクトの当たり判定（横幅）
float HitObjectBase::GetHitH() { return hitH; }//このオブジェクトの当たり判定（縦幅）

//攻撃した側（当たる側）がこの判定を呼び出す
bool HitObjectBase::HitJudge(HitObjectBase& you) {
	
	//当たり判定を作成し、判定
	if (this->hitX <= you.hitX + you.hitW) {
		if (this->hitX + this->hitW >= you.hitX) {
			if (this->hitY <= you.hitY + you.hitH) {
				if (this->hitY + this->hitH >= you.hitY) {
					//当たり判定が重なっている
					return true;

				}
			}
		}
	}
	//当たり判定は重なっていない
	return false;
}

//めり込まない移動
void HitObjectBase::ObjectMove(float preX, float preY) {

	while (preX != 0) {
		int save_x = GetPosX();
		if (preX >= 1) { AddPosX(1); preX -= 1; }
		else if (preX <= -1) { AddPosX(-1); preX += 1; }
		else { AddPosX(preX); preX = 0; }

		//当たり判定の位置更新
		UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2),this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));

		//判定がヒットしたら
		if (Map::MapCheckHit(GetHitX(), GetHitY(), GetHitW(), GetHitH())) {
			//移動キャンセル
			SetPos(save_x,GetPosY());
			//速度リセット
			ResetNowSpeedX();
			//当たり判定の位置更新
			UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
		}
	}

	while (preY != 0) {
		int save_y = GetPosY();
		if (preY >= 1) { AddPosY(1); preY -= 1; }
		else if (preY <= -1) { AddPosY(-1); preY += 1; }
		else { AddPosY(preY); preY = 0; }

		//当たり判定の位置更新
		UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2),this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));

		//判定がヒットしたら
		if (Map::MapCheckHit(GetHitX(), GetHitY(), GetHitW(), GetHitH())) {
			//移動キャンセル
			SetPos(GetPosX(), save_y);
			//速度リセット
			ResetNowSpeedY();
			//当たり判定の位置更新
			UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
		}
	}
}