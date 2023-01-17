#include "Object.h"

//���͒l�ɏ㏑��
void Object::SetPos(float x_, float y_) { this->x = x_, this->y = y_; }
void Object::SetSize(float w_, float h_) { this->w = w_; this->h = h_; }
void Object::SetSrcPos(int dx_, int dy_) { this->dx = dx_; this->dy = dy_; }
void Object::SetSrcSize(int dw_, int dh_) { this->dw = dw_; this->dh = dh_; }
void Object::SetMaxSpeed(float maxX, float maxY) { this->maxSpeedX = maxX; this->maxSpeedY = maxY; }

//�l�����Z�b�g
void Object::ResetNowSpeed() { this->nowSpeedX = 0; this->nowSpeedY = 0; }
void Object::ResetNowSpeedX() { this->nowSpeedX = 0; }
void Object::ResetNowSpeedY() { this->nowSpeedY = 0; }

//�w��̕ϐ��̒l��߂�l�Ƃ��Ď󂯎��
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

//�w��̕ϐ��ɉ��Z
void Object::AddPosX(float value) { x += value; }
void Object::AddPosY(float value) { y += value; }

//�����ibool = true -> �ō����x�ȏ�Ȃ�␳�j
void Object::AddSpeedX(float value, bool adjustment) {
	//�܂�����
	if (nowSpeedX < maxSpeedX && nowSpeedX > -maxSpeedX) {
		nowSpeedX += value;
	}
	//���x�̕␳
	if (adjustment) {
		if (nowSpeedX > maxSpeedX) {
			nowSpeedX = maxSpeedX;
		}
		else if (nowSpeedX < -maxSpeedX) {
			nowSpeedX = -maxSpeedX;
		}
	}

}
//�����ibool = true -> �ō����x�ȏ�Ȃ�␳�j
void Object::AddSpeedY(float value, bool adjustment) {
	//�܂�����
	if (nowSpeedY < maxSpeedY && nowSpeedY > -maxSpeedY) {
		nowSpeedY += value;
	}
	if (adjustment) {
		//���x�̕␳
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

//���x����
void Object::SpeedFrictionX(float power) {
	nowSpeedX /= power;
}

//�d��
void Object::AddGravity(float power) {
	AddSpeedY(power, false);
}

//���X�g����폜����ꍇ��true��
void Object::SetRemoveFlag(bool remove) { removeSinceList = remove; }
bool Object::GetRemoveFlag() { return removeSinceList; }
