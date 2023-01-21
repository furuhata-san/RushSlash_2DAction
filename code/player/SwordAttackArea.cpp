#include "SwordAttackArea.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/DataLoader.h"

SwordAttackArea::SwordAttackArea(float posX, float posY, float sizeW, float sizeH, int damage) {

	image = &Loader::swordAttackImg;

	//�`����W�ƁA�摜�̎Q�ƈʒu��ݒ�
	SetPos(posX, posY);
	SetSize(sizeW, sizeH);
	SetSrcPos(0, 0);
	SetSrcSize(192, 192);

	animNum = 0;
	animCount = 0;
	animLimit = 10;

	//�����蔻����쐬
	this->CreateHitBase(GetPosX(), GetPosY(), GetSizeW(), GetSizeH());

	//�_���[�W�ݒ�
	SetDamage(damage);

	//���g�̃^�C�v���ꎞ�I�ɖ�����
	SetMyType(Non);
	//���g�̃q�b�g�Ώۂ͂Ȃ�
	SetHitType(Non);

	//�U���t���[����ݒ�
	SettingAttackFlame(15,25);

	//���݂̃J�E���g�����Z�b�g
	ResetNowCount();

	//�폜���[�h�𖳌���
	SetRemoveFlag(false);
}

void SwordAttackArea::finalize() {
	//Nop
}

void SwordAttackArea::update() {

	nowCountUp();

	//�U���J�n�t���[�����߂����ꍇ
	if (JudgeAttackStert()) {
		//���g�̃^�C�v���v���C���[�̍U����
		SetMyType(AttackPlayer);
		//�A�j���[�V�������X�V
		AnimationUpdate();
	}

	//�U���t���[���I�����A�A�j���[�V�����I����
	if (JudgeAttackEnd()) {
		if (animNum >= animLimit) {
			SetRemoveFlag(true);//�폜�v��
		}
	}
}

void SwordAttackArea::draw() {
	//�U���J�n�t���[�����߂��Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
	if (!JudgeAttackStert()) return;

	//�G�t�F�N�g����`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
		this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH(),
		this->GetPosDX(), this->GetPosDY(),
		this->GetSizeDW(), this->GetSizeDH(),
		*image, true);

	/*
	if (JudgeAttackStert()) {
		float posX = GetHitX() - ViewData::renderPosX;
		float posY = GetHitY();
		DrawBox(posX, posY ,posX + GetHitW(), posY + GetHitH(), 125, true);
	}
	*/
}

void SwordAttackArea::AnimationUpdate() {

	//�J�E���g����
	animCount++;

	//�C���^�[�o���𒴂�����A�j���[�V����
	int interval = 1;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
	}

	//�摜�Q�ƈʒu�ύX
	if (animNum < animLimit) {
		SetSrcPos((GetSizeDW() * (animNum % 5)), (GetSizeDH() * (animNum / 5)));
	}
}
