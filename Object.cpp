#include "Object.h"

//入力値に上書き
void Object::SetPos(float x_, float y_) { this->x = x_, this->y = y_; }
void Object::SetSize(float w_, float h_) { this->w = w_; this->h = h_; }
void Object::SetSrcPos(int dx_, int dy_) { this->dx = dx_; this->dy = dy_; }
void Object::SetSrcSize(int dw_, int dh_) { this->dw = dw_; this->dh = dh_; }
void Object::SetMaxSpeed(float maxX, float maxY) { this->maxSpeedX = maxX; this->maxSpeedY = maxY; }

//値をリセット
void Object::ResetNowSpeed() { this->nowSpeedX = 0; this->nowSpeedY = 0; }
void Object::ResetNowSpeedX() { this->nowSpeedX = 0; }
void Object::ResetNowSpeedY() { this->nowSpeedY = 0; }

//指定の変数の値を戻り値として受け取る
float Object::GetPosX() { return x; };
float Object::GetPosY() { return y; };
float Object::GetSizeW() { return w; };
float Object::GetSizeH() { return h; };
int Object::GetPosDX() { return dx; };
int Object::GetPosDY() { return dy; };
int Object::GetSizeDW() { return dw; };
int Object::GetSizeDH() { return dh; };
float Object::GetNowSpeedX() { return nowSpeedX; }
float Object::GetNowSpeedY() { return nowSpeedY; }

//指定の変数に加算
void Object::AddPosX(float value) { x += value; }
void Object::AddPosY(float value) { y += value; }

//加速（bool = true -> 最高速度以上なら補正）
void Object::AddSpeedX(float value, bool adjustment) {
	//まず加速
	if (nowSpeedX < maxSpeedX && nowSpeedX > -maxSpeedX) {
		nowSpeedX += value;
	}
	//速度の補正
	if (adjustment) {
		if (nowSpeedX > maxSpeedX) {
			nowSpeedX = maxSpeedX;
		}
		else if (nowSpeedX < -maxSpeedX) {
			nowSpeedX = -maxSpeedX;
		}
	}

}
//加速（bool = true -> 最高速度以上なら補正）
void Object::AddSpeedY(float value, bool adjustment) {
	//まず加速
	if (nowSpeedY < maxSpeedY && nowSpeedY > -maxSpeedY) {
		nowSpeedY += value;
	}
	if (adjustment) {
		//速度の補正
		if (nowSpeedY > maxSpeedY) {
			nowSpeedY = maxSpeedY;
		}
		/*
		else if (nowSpeedY < -maxSpeedY) {
			nowSpeedY = -maxSpeedY;
		}
		*/
	}
}

//速度減少
void Object::SpeedFrictionX(float power) {
	nowSpeedX /= power;
}

//重力
void Object::AddGravity(float power) {
	AddSpeedY(power, false);
}

//リストから削除する場合はtrueに
void Object::SetRemoveFlag(bool remove) { removeSinceList = remove; }
bool Object::GetRemoveFlag() { return removeSinceList; }
