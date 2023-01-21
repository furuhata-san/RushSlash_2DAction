#include "../base/Effects.h"
#include "../tool/ViewData.h"

void CreateEffect(const Obj& obj) {
	Game::AddList_AddBack(obj);
}

Effect::Effect(
	int* imageAddress,
	float x,
	float y,
	float w,
	float h,
	float dx,
	float dy,
	float dw,
	float dh,
	AnimMode animMode,
	bool UI_Mode,
	bool firstDrawing,
	float playSpeed,
	int cutTotal,
	int turnNum
) {
	image = imageAddress;
	nowMode = animMode;
	SetPos(x, y);
	SetSize(w, h);
	SetSrcPos(dx, dy);
	SetSrcSize(dw, dh);
	UIMode = UI_Mode;
	drawFlag = firstDrawing;
	this->speed = playSpeed;
	imageCutTotalNum = cutTotal;
	imageTurnNum = turnNum;
	SetRemoveFlag(false);
}

void Effect::finalize() {
	//nop
}

void Effect::update() {

	//�w��̃��[�h�̏ꍇ�ɂ��ꂼ�ꏈ�����s��
	switch (nowMode)
	{

	case flashing:
		counter += 0.1f;
		if (counter >= speed) {//�C���^�[�o���𒴂�����
			drawFlag = !drawFlag;//�t���O���]
			counter = 0;//�J�E���g���Z�b�g
		}
		break;

	case animationLoop:
		counter += speed;
		//�J�E���g�ɂ���ĉ摜�̎Q�ƈʒu��ύX
		SetSrcPos(
			GetSizeDW() * ((int)counter % (imageCutTotalNum / (imageTurnNum + 1))),
			GetSizeDH() * ((int)counter / (imageCutTotalNum / (imageTurnNum + 1)))
		);
		break;

	case animationOnce:
		counter += speed;
		//�J�E���g�ɂ���ĉ摜�̎Q�ƈʒu��ύX
		SetSrcPos(
			GetSizeDW() * ((int)counter % (imageCutTotalNum / (imageTurnNum + 1))),
			GetSizeDH() * ((int)counter / (imageCutTotalNum / (imageTurnNum + 1)))
		);
		//�A�j���[�V�������I��������폜�v��
		if (counter >= imageCutTotalNum) {
			SetRemoveFlag(true);
		}
		break;

	default:
		//nop
		break;
	}
}

void Effect::draw() {

	//�t���O���L���Ȃ�`��
	if (drawFlag) {
		//UI�ł͂Ȃ��ꍇ�̓X�N���[���Ή�
		float X = GetPosX();
		if (!UIMode) {
			X -= ViewData::GetRenderPosX();
		}

		DrawRectExtendGraphF(
			X,
			GetPosY(),
			X + GetSizeW(),
			GetPosY() + GetSizeH(),
			GetPosDX(),
			GetPosDY(),
			GetSizeDW(),
			GetSizeDH(),
			*image,
			true);
	}
}