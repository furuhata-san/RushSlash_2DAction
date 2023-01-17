#include "Dxlib.h"
#include <time.h>
#include "Player.h"
#include "KeyChecker.h"
#include "SceneMgr.h"
#include "DataLoader.h"
#include "Map.h"
#include "ViewData.h"
#include "GameMgr.h"
//�U���G���A
#include "SwordAttackArea.h"
#include "FireAttackArea.h"
#include "Effects.h"

//�R���X�g���N�^�@���̉����ɍs���鏈��
Player::Player(float posX, float posY) {
	//�摜�ǂݍ��݁i�ۑ��̈悩��j
	image = &Loader::playerImg;

	//���W�̏�����
	SetPos(posX, posY);
	SetSize(140, 140);

	//�`��ʒu�̏�����
	SetSrcPos(0, 0);
	SetSrcSize(140, 140);

	//�ړ����x�̐ݒ�
	SetMaxSpeed(20, 100);
	runForce = 8.5f;
	jumpForce = 20.5f;
	ResetNowSpeed();

	//�̗͂̐ݒ�
	hpMax = 10;
	hp = hpMax;

	//���U���g�\�����Ɏg�p
	GameResultFlag = true;

	//�A�j���[�V�����J�E���g�����Z�b�g
	animCounterReset();

	//���g�̃^�C�v�ƃq�b�g�^�C�v��ݒ�
	SetHitType(HitObjectType::AllHit);
	SetMyType(HitObjectType::Player);

	//�ŏ��̃��[�V������ݒ�
	this->motion = Motion::idle;
	this->angle = Angle::right;

	//�폜���Ȃ�
	SetRemoveFlag(false);

	InvincibleInitialize_Time(90);//���G���ԏ�����

	//�����蔻��쐬
	CreateHitBase(this->GetPosX(), this->GetPosY(), 60, 100);//���g�̓����蔻��
}

//�I��
void Player::finalize() {
	//�����~�߂�
	int* dieSE = &Loader::PlayerFallDieSE;
	StopSoundMem(*dieSE);
	int* OverSE = &Loader::GameOverSE;
	StopSoundMem(*OverSE);
	int* ClearSE = &Loader::GameClearSE;
	StopSoundMem(*ClearSE);
}

//�X�V
void Player::update() {
	
	//���͂ɂ�胂�[�V�����X�V
	MotionUpdate(this->motion);

	//���[�V�����ɂ�菈���X�V
	PlayMotion(this->motion);

	//�A�j���[�V�������S�ʂ̍X�V
	animMotionUpdate();

	PlayerGameClear();

	//�����蔻��̈ʒu�X�V
	UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
}

//�`��
void Player::draw() {

	//�A���O���������̏ꍇ�͕`��𔽓]
	bool mirrorFlag = false;
	if (this->angle == Angle::left) mirrorFlag = true;

	//���G�ł͂Ȃ��ꍇ�i���ʏ�`��j�@�������́@���G���J�E���g����萔���܂��Ă���ꍇ�i���_�ł���j
	if (!GetIncincible_Time() || GetIncincible_Count() % 5 == 0) {
		//�L������`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
		//�X�N���[���Ή��ς�
		DrawRectGraphF(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
			this->GetPosDX(), this->GetPosDY(),
			this->GetSizeDW(), this->GetSizeDH(),
			*image, TRUE, mirrorFlag);
	}

	//���C�t�Q�[�W�`��
	DrawLifeGaugeUI();
}

void Player::MotionUpdate(Motion& nowMotion) {
	
	//�����ł́A�v���C���[�̃��[�V�������ƂɁA
	//���͂��󂯎��A���[�V�������`�F���W����
	//�P�[�X���Ƃɏ��������

	switch (nowMotion) {

		//�D��x�̍������ɋL��

	case idle:
		//�n�ʂ��Ȃ��ꍇ�͗�����Ԃ�
		if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
			MotionChange(Motion::jump, false);
		}
		//�W�����v([W][UP])
		else if (KeyChecker::InputDown(KEY_INPUT_W) || KeyChecker::InputDown(KEY_INPUT_UP)) {
			MotionChange(Motion::jump, true);
		}
		//���ōU��([J][Z])
		else if (KeyChecker::InputDown(KEY_INPUT_J) || KeyChecker::InputDown(KEY_INPUT_Z)) {
			MotionChange(Motion::sword, true);
		}
		//���@���g��([K][X])
		else if (KeyChecker::InputDown(KEY_INPUT_K) || KeyChecker::InputDown(KEY_INPUT_X)) {
			MotionChange(Motion::magic, true);
		}
		//�ړ��L�[�̓��͂ňړ���Ԃ�([A][D][Left][Right])
		else if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) { 
			MotionChange(Motion::run, true);
		}
		else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
			MotionChange(Motion::run, true);
		}
		break;

	case sword:
		//�A�j���[�V�����I�����@�ҋ@��Ԃ�
		if (animNum >= 3) {
			MotionChange(Motion::idle, false);
		}
		break;

	case magic:
		//���@�����߂�
		if (magicChargeValue <= 640) {
			//�w��񐔖��ɃG�t�F�N�g����
			if (magicChargeValue % 100 == 0) {
				//�G�t�F�N�g����
				float sizeW = 250.0f;
				float sizeH = 250.0f;
				Obj createObj =
					Obj(new Effect(
						&Loader::MagicChargeEffect,
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
						1.0f,
						30,
						5
					));
				CreateEffect(createObj);
			}

			//�J�E���g�A�b�v
			magicChargeValue += 10;
		}

		//�L�[���͂��Ȃ��Ȃ������@�ҋ@��Ԃ֕ύX���A�^�C�~���O�ɂ���Ė��@�𔭓�
		if (!KeyChecker::InputOn(KEY_INPUT_K) && !KeyChecker::InputOn(KEY_INPUT_X)) {

			//���̖��@
			float areaSizeW = magicChargeValue;
			float areaSizeH = 240;
			float areaPosX = GetHitX() - ((areaSizeW - GetHitW()) / 2);
			float areaPosY = GetHitY() - (areaSizeH / 2);
			int damageValue = magicChargeValue / 10;

			hObj object(new FireAttackArea(areaPosX, areaPosY, areaSizeW, areaSizeH, damageValue));
			CraeteAttackArea(object);

			MotionChange(Motion::idle, false);

			//���@�̂��߂��O��
			magicChargeValue = 0;
		}
		break;

	case win:
		break;

	case run:
		//�ړ��L�[�����͂���Ă����ꍇ�͌�����ݒ�
		if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
			angle = Angle::left;
		}
		else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
			angle = Angle::right;
		}
		else {//������Ă��Ȃ��ꍇ�́A�ҋ@��Ԃ�
			MotionChange(Motion::idle, false);
		}

		//�n�ʂ��Ȃ��ꍇ�͗�����Ԃ�
		if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
			MotionChange(Motion::jump, false);
		}
		//�W�����v([W][UP])
		else if (KeyChecker::InputDown(KEY_INPUT_W) || KeyChecker::InputDown(KEY_INPUT_UP)) {
			MotionChange(Motion::jump, true);
		}
		//���ōU��([J][Z])
		else if (KeyChecker::InputDown(KEY_INPUT_J) || KeyChecker::InputDown(KEY_INPUT_Z)) {
			MotionChange(Motion::sword, true);
		}
		//���@���g��([K][X])
		else if (KeyChecker::InputDown(KEY_INPUT_K) || KeyChecker::InputDown(KEY_INPUT_X)) {
			MotionChange(Motion::magic, true);
		}
		break;

	case jump:
		//���n������ҋ@��Ԃ�
		if (Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
			MotionChange(Motion::idle, false);
		}
		//�����Ԃ������瑬�x���Z�b�g
		else if (Map::MapCheckHit(GetHitX(), GetHitY() - 1, GetHitW(), 1)) {
			this->ResetNowSpeedY();
		}

		break;

	case damage:
		//���n�������Ԃ�ύX��
		if (GetNowSpeedY() >= 0) {
			if (Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
				if (hp > 0) {//�̗͂��c���Ă���ꍇ
					SetIncincible_Time();//���G�ɂȂ�
					MotionChange(Motion::idle, false);//�ҋ@��Ԃ�
				}
				else{//�̗͂��c���Ă��Ȃ��ꍇ
					MotionChange(Motion::die, false);//���S��Ԃ�
				}
			}
		}
		break;

	case die:
		break;
	}

	//���@�`���[�W���ł͂Ȃ��ꍇ
	if (nowMotion != magic) {
		//�`���[�W�ʃ��Z�b�g
		magicChargeValue = 0;
	}


	//��������
	PlayerFallHole();
}

//���̃��[�V�����ƁA�A�N�V�������s�����ǂ���
Player::Motion Player::MotionChange(const Motion chengeotion, bool action) {
	//���̊֐��iMotionChenge�j���Ă΂ꂽ�ꍇ�A
	//�����ɂ���ď������s��

	int* nowSoundMem = 0; //���ʉ��̃|�C���^

	if (action) {//�A�N�V�������s���ꍇ�́A�������s��
		switch (chengeotion) {
		case idle:
			break;

		case sword:
		{
			motion = Motion::sword;	//���U����Ԃ֕ύX
			animCounterReset();	//�A�j���[�V��������x���Z�b�g

			//�U��������쐬
			float swordAreaW = 150;
			float swordAreaH = 150;

			//�����ɂ���ďꏊ�𒲐�
			float areaPosX;
			if (angle == left) {
				areaPosX = GetHitX() - (swordAreaW);
			}
			else {
				areaPosX = GetHitX() + GetHitW();
			}
			float areaPosY = GetPosY() - ((swordAreaH - GetHitH()) / 2);

			hObj object(new SwordAttackArea(areaPosX, areaPosY, swordAreaW, swordAreaH, 30));
			CraeteAttackArea(object);

			nowSoundMem = &Loader::PlayerSwoadSE;//���ʉ��̃A�h���X��n��
		}
			break;

		case magic:
			animCounterReset();
			break;

		case win:
			break;

		case run:
			if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
				angle = Angle::left;
			}
			else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
				angle = Angle::right;
			}
			break;

		case jump:
			//���x���Z�b�g�[������
			this->ResetNowSpeedY();
			this->AddSpeedY(-jumpForce,true);
			nowSoundMem = &Loader::PlayerJumpSE;//���ʉ��̃A�h���X��n��
			break;

		case damage:
			this->AddSpeedY(-jumpForce / 2, true);	//�m�b�N�o�b�N
			if (hp > 0) {//����ł��Ȃ��ꍇ
				nowSoundMem = &Loader::PlayerDamageSE;//���ʉ��̃A�h���X��n��
			}
			else {//���񂾏ꍇ
				nowSoundMem = &Loader::PlayerHpZeroDieSE;//���ʉ��̃A�h���X��n��
			}
			break;

		case die:
			nowSoundMem = &Loader::PlayerFallDieSE;//���ʉ��̃A�h���X��n��
			break;
		}
	}

	//�A�h���X���ǂݍ��܂�Ă���ꍇ
	if (nowSoundMem != 0) {
		int playSound = *nowSoundMem;
		//���ʉ���炷
		PlaySoundMem(playSound, DX_PLAYTYPE_BACK);
	}
	
	//���[�V�����ύX
	return motion = chengeotion;
}


void Player::PlayMotion(Motion nowMotion) {

	//�����ł́A���[�V�������Ƃ̃v���C���̏������L�q����

	//�P�[�X���Ƃɏ��������
	switch (nowMotion) {
	case idle:
		break;

	case sword:

		break;

	case magic:
		break;

	case win:

		if (GameResultFlag) {
			//BGM���~�߂�
			int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
			StopSoundMem(*bgmAddress);

			//�����쐬(GameClear, PressEnter)
			//Clear
			Obj createObj =
				Obj(new Effect(
					&Loader::gameclearText,
					(ViewData::size_w / 2) - (543.0f / 2 * 2),
					250.0f,
					543.0f * 2,
					114.0f * 2,
					0.0f,
					0.0f,
					543.0f,
					114.0f,
					Effect::AnimMode::normal,
					true
				));
			CreateEffect(createObj);

			//Enter
			createObj =
				Obj(new Effect(
					&Loader::pressEnterText,
					(ViewData::size_w / 2) - (590.0f / 2),
					550.0f,
					590.0f,
					107.0f,
					0.0f,
					0.0f,
					590.0f,
					107.0f,
					Effect::AnimMode::flashing,
					true,
					true,
					3.0f
				));
			CreateEffect(createObj);

			//�Q�[���I�[�o�[���ʉ�
			int* seAddress = &Loader::GameClearSE;

			PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

			//�t���O���I�t��
			GameResultFlag = false;
		}

		if (KeyChecker::InputUp(KEY_INPUT_RETURN)) {
			ChengeScene(new TitleScene);
		}
		break;

	case run:
		//�����Ă�������ɂ���ĉ�������
		if (angle == right) {
			this->AddSpeedX(runForce, true);
		}
		else {
			this->AddSpeedX(-runForce, true);
		}
		break;

	case jump:
		//�L�[���͕����ֈړ�
		if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
			this->AddSpeedX(runForce / 1.5f, true);
		}
		else if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
			this->AddSpeedX(-runForce / 1.5f, true);
		}

		break;

	case damage:
		//�����Ă�������̋t�����ɉ�������
		if (angle == right) {
			this->AddSpeedX(-runForce / 2, true);
		}
		else {
			this->AddSpeedX(runForce / 2, true);
		}
		break;

	case die:
		this->ResetNowSpeed();

		if (GameResultFlag) {
			//BGM���~�߂�
			int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
			StopSoundMem(*bgmAddress);

			//�����쐬(GameOver, PressEnter)
			//Over
			Obj createObj =
				Obj(new Effect(
					&Loader::gameoverText,
					(ViewData::size_w / 2) - (430 / 2 * 2),
					200.0f,
					430.0f * 2,
					128.0f * 2,
					0.0f,
					0.0f,
					430.0f,
					127.0f,
					Effect::AnimMode::normal,
					true
				));
			CreateEffect(createObj);

			//Enter
			createObj =
				Obj(new Effect(
					&Loader::pressEnterText,
					(ViewData::size_w / 2) - (590.0f / 2),
					500.0f,
					590.0f,
					107.0f,
					0.0f,
					0.0f,
					590.0f,
					107.0f,
					Effect::AnimMode::flashing,
					true,
					true,
					3.0f
				));
			CreateEffect(createObj);

			//�Q�[���I�[�o�[���ʉ�
			int* seAddress = &Loader::GameOverSE;

			PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

			//�t���O���I�t��
			GameResultFlag = false;
		}

		if (KeyChecker::InputUp(KEY_INPUT_RETURN)) {
			ChengeScene(new TitleScene);
		}

		break;
	}

	//��ɓ��삷�����

	//���C
	this->SpeedFrictionX(2.0f);

	//�d�͉���
	if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
		this->AddGravity(1.0f);
	}

	//�ڒn���m�肵�Ă���ہA�d�͌v�Z�����Z�b�g
	if (motion == Motion::idle || motion == Motion::run) {
		this->ResetNowSpeedY();
	}

	//�߂荞�܂Ȃ��ړ�
	this->ObjectMove(this->GetNowSpeedX(), this->GetNowSpeedY());
}

//�v���C���[�����ɗ��������ǂ����𔻒f���A�������s��
void Player::PlayerFallHole() {

	//���S���Ă���ꍇ�A�������s��Ȃ�
	if (motion == Motion::die)return;

	//�v���C����Y���W���X�N���[���O�������ꍇ
	if (this->GetPosY() > ViewData::size_h) {
		MotionChange(Motion::die, true);
	}
}

void Player::animMotionUpdate() {

	if (!this->imageNullChecker(motion)) {
		animNum = 0;
		this->SetSrcPos(this->animNum * this->GetSizeDW(), this->motion * this->GetSizeDH());
		return;
	}

	//�J�E���g����
	this->animCount += 1;
	int moveMotionNum = 4;

	//�C���^�[�o���𒴂�����A�j���[�V����
	int interval = 8;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
		if (this->animNum >= moveMotionNum) {
			this->animNum = 0; 
		}
	}

	//�`��ʒu�̐ݒ���X�V
	this->SetSrcPos(this->animNum * this->GetSizeDW(), this->motion * this->GetSizeDH());
}

void Player::HitMove(HitObjectBase& you) {
	//�U�����Ă��Ȃ� + �_���[�W���󂯂Ă��Ȃ� + ����ł��Ȃ�
	if (motion == sword) return;
	if (motion == damage) return;
	if (motion == die) return;

	if (you.GetMyType() == Enemy) {
		//���G�̏ꍇ�͏������s��Ȃ�
		if (GetIncincible_Time()) { return; }

		//�̗͌���
		hp -= 1;

		//�m�b�N�o�b�N
		ResetNowSpeed();//���x���Z�b�g
		//�����̕ύX
		if (you.GetPosX() <= this->GetPosX()) {//���g��荶��you�������ꍇ
			this->angle = Angle::left;
		}
		else {//���g���E��you�������ꍇ
			this->angle = Angle::right;
		}
		//���[�V�����ύX
		MotionChange(Motion::damage, true);
	}
}

void Player::PlayerGameClear() {
	if (motion == win) { return; }//�|�[�Y�������Ȃ珈���͍s��Ȃ�
	if (motion == die) { return; }//�|�[�Y�����S�Ȃ珈���͍s��Ȃ�
	if (Game::clearJudge()) {
		//���[�V�����ύX
		MotionChange(Motion::win, true);
		//BGM���~�߂�
		int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
		StopSoundMem(*bgmAddress);
	}
}

void Player::CraeteAttackArea(hObj& hobj) {
	Game::AddList_AddBack(hobj);
}

void Player::DrawLifeGaugeUI() {

	//����W
	float dx = this->GetPosX() - ViewData::GetRenderPosX() - 25;
	float dy = this->GetPosY() - 50;

	//�T�C�Y�w��
	int sizeW = 913;
	int sizeH = 300;
	int srcX = 0;
	int srcY = 0;

	float magnification = 0.2f;

	//�Q�[�W�w�i�[���Q�[�W�[���J�o�[�̏��ŕ`��

	//�Q�[�W�w�i
	int* backImg = &Loader::PlayerGaugeBackImg;
	DrawRectExtendGraphF(dx, dy, dx + sizeW * magnification, dy + sizeH * magnification,
		srcX, srcY, sizeW, sizeH, *backImg, true);

	//�Q�[�W
	int* gaugeImg = &Loader::PlayerGaugeImg;
	int sizeLifeW = (sizeW / this->hpMax) * hp;
	//�L������`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF(dx, dy, dx + sizeLifeW * magnification, dy + sizeH * magnification,
		srcX, srcY, sizeLifeW, sizeH, *gaugeImg, true);


	//�Q�[�W�J�o�[
	int* coverImg = &Loader::PlayerGaugeCoverImg;
	//�L������`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF(dx, dy, dx + sizeW * magnification, dy + sizeH * magnification,
		srcX, srcY, sizeW, sizeH, *coverImg, true);

	//�����̐���`��
	//�w��}�b�v�̏ꍇ�͔��A�ق��͍�
	int Color = GetColor(0, 0, 0);
	if (Map::mapNum == 2 || Map::mapNum == 3) {
		Color = GetColor(255, 255, 255);
	}
	SetFontSize(30);
	DrawFormatString(dx + 55, dy + 5, Color, "�~%d", Game::clearItemCounter);
}
