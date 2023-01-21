#include "Dxlib.h"
#include "../player/Player.h"
#include "GoalItem.h"
#include "../tool/ViewData.h"
#include "../tool/DataLoader.h"
#include "../map/Map.h"
#include "../scene/SceneMgr.h"
#include "../base/Effects.h"
#include "../scene/AddList.h"

GoalItem::GoalItem(float x, float y, int colorNum) {
	//�摜�ǂݍ��݁i�ۑ��̈悩��j
	image = &Loader::ItemImg;

	//���W�̏�����
	SetPos(x, y + ((64 - 44) / 2));
	SetSize(64, 44);

	//�`��ʒu�̏�����
	SetSrcPos(32 * colorNum, 0);
	SetSrcSize(32, 22);

	ResetNowSpeed();

	//���g�̃^�C�v�ƃq�b�g�^�C�v��ݒ�
	SetHitType(HitObjectType::Player);
	SetMyType(HitObjectType::Item);

	//�폜���Ȃ�
	SetRemoveFlag(false);

	//�����蔻��쐬
	CreateHitBase(this->GetPosX(), this->GetPosY(), GetSizeW(), GetSizeH());//���g�̓����蔻��
}

void GoalItem::finalize() {
	//Nop
}

void GoalItem::update() {

}

void GoalItem::draw() {
	//�`��ʒu�̐ݒ���X�V
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
		this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH(),
		this->GetPosDX(), this->GetPosDY(),
		this->GetSizeDW(), this->GetSizeDH(),
		*image, true);
}

void GoalItem::HitMove(HitObjectBase& you) {

	//���ʉ���炷
	int* seAddress = &Loader::GetItemSE;
	PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

	//�G�t�F�N�g����
	float sizeW = 100.0f;
	float sizeH = 100.0f;
	Obj createObj =
		Obj(new Effect(
			&Loader::GetItemEffect,
			this->GetPosX() - (sizeW / 2) + (this->GetSizeW() / 2),
			this->GetPosY() - (sizeH / 2) + (this->GetSizeH() / 2),
			sizeW,
			sizeH,
			0.0f,
			0.0f,
			200.0f,
			200.0f,
			Effect::AnimMode::animationOnce,
			false,
			true,
			1.5f,
			30,
			6
		));
	CreateEffect(createObj);
	SetRemoveFlag(true);

	//�폜
	SetRemoveFlag(true);

}