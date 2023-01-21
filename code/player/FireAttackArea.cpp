#include "FireAttackArea.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/DataLoader.h"

FireAttackArea::FireAttackArea(float posX, float posY, float sizeW, float sizeH, int damage) {

	//�C���[�W��ǂݍ���
	image = &Loader::magicFireImg;

	int* attackSE = &Loader::PlayerFireAttackSE;
	PlaySoundMem(*attackSE, DX_PLAYTYPE_BACK);

	//�`����W�ƁA�摜�̎Q�ƈʒu��ݒ�
	SetPos(posX, posY);
	SetSize(sizeW, sizeH);
	SetSrcPos(0, 0);
	SetSrcSize(640, 240);

	animNum = 0;
	animCount = 0;
	animLimit = 8;

	//�����蔻����쐬�i���������j
	this->CreateHitBase(GetPosX(), GetPosY() + (GetSizeH() / 2), GetSizeW(), GetSizeH() / 2);

	//�_���[�W�ݒ�
	SetDamage(damage);

	//���g�̃^�C�v���ꎞ�I�ɖ�����
	SetMyType(Non);
	//���g�̃q�b�g�Ώۂ͂Ȃ�
	SetHitType(Non);

	//�U���t���[����ݒ�
	SettingAttackFlame(4 * 2, 4 * (animLimit - 2));

	//���݂̃J�E���g�����Z�b�g
	ResetNowCount();

	//�폜���[�h�𖳌���
	SetRemoveFlag(false);
}

void FireAttackArea::finalize() {
	//Nop
}

void FireAttackArea::update() {

	nowCountUp();

	//�A�j���[�V�����X�V
	AnimationUpdate();

	//�U���J�n�t���[�����߂����ꍇ
	if (JudgeAttackStert()) {
		//���g�̃^�C�v���v���C���[�̍U����
		SetMyType(AttackPlayer);
	}

	//�U���t���[���I�����A�A�j���[�V�����I����
	if (JudgeAttackEnd()) {
		if (animNum >= animLimit - 2) {
			SetRemoveFlag(true);//�폜�v��
		}
	}


}

void FireAttackArea::draw() {
	
	//�G�t�F�N�g����`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
		this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH(),
		this->GetPosDX(), this->GetPosDY(),
		this->GetSizeDW(), this->GetSizeDH(),
		*image, true);
}

void FireAttackArea::AnimationUpdate() {
	
	//�J�E���g����
	animCount++;

	//�C���^�[�o���𒴂�����A�j���[�V����
	int interval = 3;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
	}

	//�摜�Q�ƈʒu�ύX
	if (animNum < animLimit) {
		SetSrcPos(0, GetSizeDH() * animNum);
	}
}
