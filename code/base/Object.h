#pragma once

/// <summary>
/// �C�����C��
/// </summary>

class Object {

	float x, y;	//XY���W
	float w, h;	//����
	int dx, dy; //�`�掞�̉���
	int dw, dh; //�`�掞�̉���

	float maxSpeedX, maxSpeedY;
	float nowSpeedX, nowSpeedY;

	bool removeSinceList;

public:
	//���͒l�ɏ㏑��
	virtual void SetPos(float x_, float y_);
	virtual void SetSize(float w_, float h_);
	virtual void SetSrcPos(int dx_, int dy_);
	virtual void SetSrcSize(int dw_, int dh_);
	virtual void SetMaxSpeed(float maxX, float maxY);

	//�l�����Z�b�g
	virtual void ResetNowSpeed();
	virtual void ResetNowSpeedX();
	virtual void ResetNowSpeedY();

	//�w��̕ϐ��̒l��߂�l�Ƃ��Ď󂯎��
	virtual float GetPosX();
	virtual float GetPosY();
	virtual float GetSizeW();
	virtual float GetSizeH();
	virtual int GetPosDX();
	virtual int GetPosDY();
	virtual int GetSizeDW();
	virtual int GetSizeDH();
	virtual float GetNowSpeedX();
	virtual float GetNowSpeedY();

	//�w��̕ϐ��ɉ��Z
	virtual void AddPosX(float value);
	virtual void AddPosY(float value);

	//�����ibool = true -> �ō����x�ȏ�Ȃ�␳�j
	virtual void AddSpeedX(float value, bool adjustment);
	//�����ibool = true -> �ō����x�ȏ�Ȃ�␳�j
	virtual void AddSpeedY(float value, bool adjustment);

	//���x����
	virtual void SpeedFrictionX(float power);

	//�d��
	virtual void AddGravity(float power);

	//���X�g����폜����ꍇ��true��
	virtual void SetRemoveFlag(bool remove);
	virtual bool GetRemoveFlag();

	//�ǉ��������֐��͈ȉ��ɋL�q


	//�I�[�o�[���C�h�p�֐��i������ȉ��͕ύX�s�j
	virtual void finalize() { /*nop*/ };//�I���E�������
	virtual void update() { /*nop*/ };//�X�V����
	virtual void draw() { /*nop*/ };//�`�揈��
};