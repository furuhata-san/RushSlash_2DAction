#include "DxLib.h"
#include "../enemy/EnemyBase.h"
#include "../tool/ViewData.h"
#include "../map/Map.h"
#include "../scene/AddList.h"
#include "../scene/GameMgr.h"
#include "../base/Effects.h"

/*

�����ɂ́A�G�l�~�[�i����̓G�j�ɋ��ʂ��鏈�����L�q����B
�����ɂ���֐��̓I�[�o�[���C�h���Ă͂����Ȃ�

*/

void EnemyBase::finalize() {
	//nop
}

void EnemyBase::update() {

	//��ʊO�ɓ����moveFlag��true��
	EnemyOnScreen();

	if (moveFlag) {
		//�A�j���[�V�����X�V
		animMotionUpdate();
		//�����蔻��̈ʒu�X�V
		UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
		//�G�l�~�[�ŗL�̓���
		EnemyOnlyMove();

		//���n���Ă��Ȃ��ꍇ�A�d�͉���
		if (!Map::MapCheckHit((int)GetHitX(), (int)GetHitY() + (int)GetHitH(), (int)GetHitW(), 1)) {
			this->AddGravity(gravityScale);
		}
		else//���n���Ă���ꍇ
		{
			if (GetNowSpeedY() >= 0) {
				if (Map::MapCheckHit((int)GetHitX(), (int)GetHitY() + (int)GetHitH(), (int)GetHitW(), 1)) {
					//�d�̓��Z�b�g
					ResetNowSpeedY();
					//���G�������ꍇ�i�q�b�g�o�b�N���A���x���Z�b�g�j
					if (GetIncincible_Bool()) {
						ResetNowSpeedX();
						SetIncincible_Bool(false);//���G����
					}
					
				}
			}
		}

		//���C
		this->SpeedFrictionX(1.0f);

		//�߂荞�܂Ȃ��ړ�
		this->ObjectMove(this->GetNowSpeedX(), this->GetNowSpeedY());

		//���ɗ�������폜�v��
		this->FallHoleRemove();

		//�N���A������
		if (Game::clearJudge()) {
			//�G�t�F�N�g����
			CreateDieEffect();
			//�폜�v��
			SetRemoveFlag(true);
		}

	}
}


void EnemyBase::draw() {
	//��ʊO�͕`�悵�Ȃ�
	if (GetPosX() + GetSizeW() - ViewData::GetRenderPosX() < 0) return;
	if (GetPosX() - ViewData::GetRenderPosX() > ViewData::gameSize_w) return;
	
	//�L������`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY() - ViewData::GetRenderPosY(),
		 this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH() - ViewData::GetRenderPosY(),
			this->GetPosDX(), this->GetPosDY(),
			this->GetSizeDW(), this->GetSizeDH(),
		*image, true);

	//HP�o�[�̕`��
	if (life != lifeMax) {//�̗͂��ő�l�ł͂Ȃ��ꍇ
		//���{�b�N�X
		DrawBox(
			int(this->GetPosX() - ViewData::GetRenderPosX()),
			int(this->GetPosY() - 15 - ViewData::GetRenderPosY()),
			int(this->GetPosX() - ViewData::GetRenderPosX() + this->GetSizeW()),
			int(this->GetPosY() - 5 - ViewData::GetRenderPosY()),
			GetColor(0, 0, 0), true);

		//�΃{�b�N�X
		int greenBoxDrawPos = (this->GetSizeW() / lifeMax) * life;
		DrawBox(int(this->GetPosX() - ViewData::GetRenderPosX()),
			int(this->GetPosY() - 15 - ViewData::GetRenderPosY()),
			int(this->GetPosX() - ViewData::GetRenderPosX() + greenBoxDrawPos),
			int(this->GetPosY() - 5 - ViewData::GetRenderPosY()),
			GetColor(0, 255, 0), true);
	}
}

void EnemyBase::animMotionUpdate() {
	//�J�E���g����
	this->animCount += 1;

	int animTable[4] = {0,1,2,1};
	int moveMotionNum = sizeof(animTable) / sizeof(animTable[0]);

	//�C���^�[�o���𒴂�����A�j���[�V����
	int interval = 8;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
		if (this->animNum >= moveMotionNum) {
			this->animNum = 0;
		}
	}

	//�J�E���g�𑝉������A���݂̃A�j���[�V������ۑ�
	++angleMoveNum;
	int animChangeInterval = 10;

	//�����ɂ���ď������X�V
	//�u���E���΂߁��O�と�΂߁��ŏ��Ƃ͔��΂̌����v
	switch (animAngle)
	{
	case tofront://����
		if (angleMoveNum >= animChangeInterval) {
			angleMoveNum = 0;
			if (saveAnimAngle == inleft) {
				animAngle = inright;
			}
			else  if (saveAnimAngle == inright) {
				animAngle = inleft;
			}
			saveAnimAngle = tofront;
		}
		break;

	case toleft://���S�ɍ�
		angleMoveNum = 0;
		saveAnimAngle = toleft;
		break;

	case toright://���S�ɉE
		angleMoveNum = 0;
		saveAnimAngle = toright;
		break;

	case toback://���
		if (angleMoveNum >= animChangeInterval) {
			angleMoveNum = 0;
			if (saveAnimAngle == outleft) {
				animAngle = outright;
			}
			else  if (saveAnimAngle == outright) {
				animAngle = outleft;
			}
			saveAnimAngle = toback;
		}
		break;

	case inleft://���΂߉�
		if (angleMoveNum >= animChangeInterval) {
			angleMoveNum = 0;
			if (saveAnimAngle == tofront) {
				animAngle = toleft;
			}
			else{
				animAngle = tofront;
			}
			saveAnimAngle = inleft;
		}
		break;

	case inright://�E�΂߉�
		if (angleMoveNum >= animChangeInterval) {
			angleMoveNum = 0;
			if (saveAnimAngle == tofront) {
				animAngle = toright;
			}
			else{
				animAngle = tofront;
			}
			saveAnimAngle = inright;
		}
		break;

	case outleft://�����
		if (angleMoveNum >= animChangeInterval) {
			angleMoveNum = 0;
			if (saveAnimAngle == toback) {
				animAngle = toleft;
			}
			else{
				animAngle = toback;
			}
			saveAnimAngle = outleft;
		}
		break;

	case outright://�E���
		if (angleMoveNum >= animChangeInterval) {
			angleMoveNum = 0;
			if (saveAnimAngle == toback) {
				animAngle = toright;
			}
			else {
				animAngle = toback;
			}
			saveAnimAngle = outright;
		}
		break;

	default:
		break;
	}


	//�`��ʒu�̐ݒ���X�V
	this->SetSrcPos((((this->animAngle / 4) * 3) + animTable[animNum]) * this->GetSizeDW(),
						((this->animAngle % 4)) * this->GetSizeDH());
}

//�q�b�g�^�C�v�̃I�u�W�F�N�g�Ƃ̓����蔻�肪�L�������ꂽ�ꍇ
void EnemyBase::HitMove(HitObjectBase& you) {

	//���G�̏ꍇ�͏������s��Ȃ�
	if (GetIncincible_Bool()) { return; }

	//�m�b�N�o�b�N�̂��߃X�s�[�h�����Z�b�g
	ResetNowSpeed();

	//�����蔻��̈ʒu�ɂ���ăm�b�N�o�b�N���s��
	float youX = ViewData::GetPlayerWorldPosX();

	//�uyou�v��荶��
	if (this->GetHitX() <= youX) {
		animAngle = AnimAngle::toright;
		this->AddSpeedX(-hitBackSpeed, false);//���Ɉړ�
		this->AddSpeedY(-hitBackSpeed, true);//�W�����v
	}
	else { //�uyou�v���E��
		animAngle = AnimAngle::toleft;
		this->AddSpeedX(hitBackSpeed,false); //�E�Ɉړ�
		this->AddSpeedY(-hitBackSpeed,true); //�W�����v
	}

	//�̗͌���
	AddLife(-you.GetDamage());

	//���ʉ�
	int* seAddress;
	//�̗͂��Ȃ��Ȃ�����
	if (LifeIsZero()) {
		//���ʉ��̃A�h���X�擾
		seAddress = &Loader::EnemyDieSE;
		//�G�t�F�N�g����
		CreateDieEffect();
		
		SetRemoveFlag(true); //�폜
	}
	else {//�̗͂��c���Ă�����
		//���ʉ��̃A�h���X�擾
		seAddress = &Loader::EnemyDamageSE;
	}
	//���łɓ����������Ă�����~�߂�i���邳���Ȃ邽�߁j
	if (CheckSoundMem(*seAddress)) {
		StopSoundMem(*seAddress);
	}
	PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

	//�Ō�ɖ��G��Ԃɂ���(�m�b�N�o�b�N���̓q�b�g���Ă��_���[�W���󂯂Ȃ�)
	SetIncincible_Bool(true);
}

//�G�l�~�[����ʓ��ɕ`�悳��Ă����ꍇ��MoveFlag��true�ɂ���
void EnemyBase::EnemyOnScreen() {
	
	//��ʊO�͏������s��Ȃ�
	if (GetPosX() + GetSizeW() - ViewData::GetRenderPosX() < 0) return;
	if (GetPosX() - ViewData::GetRenderPosX() > ViewData::gameSize_w) return;

	SetMoveFlag(true);
}

void EnemyBase::FallHoleRemove() {
	if (GetPosY() > ViewData::gameSize_h) {
		//�G�t�F�N�g����
		CreateDieEffect();

		//�폜�v��
		SetRemoveFlag(true);
	}
}

void EnemyBase::CreateDieEffect() {
	//�G�t�F�N�g����
	float sizeW = 250.0f;
	float sizeH = 250.0f;
	Obj createObj =
		Obj(new Effect(
			&Loader::EnemyDieEffect,
			this->GetPosX() - (sizeW / 2) + (this->GetSizeW() / 2),
			this->GetPosY() - (sizeH / 2) + (this->GetSizeH() / 2),
			sizeW,
			sizeH,
			0.0f,
			0.0f,
			300.0f,
			300.0f,
			Effect::AnimMode::animationOnce,
			false,
			true,
			1.5f,
			30,
			5
		));
	CreateEffect(createObj);
}