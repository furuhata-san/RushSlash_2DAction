#pragma once

/// <summary>
/// 
/// �摜��Wave���Ƃɕ����ēǂݍ��݁A
/// �I�����ɑS�J�����邱�ƂƂ���B
/// 
/// �����ɂ���f�[�^�̓|�C���^�ŎQ�Ƃ��A
/// �摜�̃R�s�[���͋֎~�Ƃ���B
/// 
/// cpp�ɓǂݍ��ޏ��Ԃ��L�ڂ��邱�ƁB
/// 
/// �܂��A�V�[�����Ƃɓǂݍ��݂����摜��������ꍇ�́A
/// �V�[���N���X�œǂݍ��݂��s���B
/// 
/// �܂��A�����ɂ���֐��̓v���W�F�N�g�S�̂�
/// ��񂾂������Ă�ł͂Ȃ�Ȃ��B
/// �i�E�F�[�u�̌Ăяo�����Ԃ͂̓o���o���ł��j
/// </summary>

namespace Loader {

	//�摜�̕ۑ��̈��錾
	//�錾������͕ϐ��̎��̂�錾���Acpp���̍폜�R�[�h�ɒǉ�
	extern int playerImg;
	extern int mapBlockImg;
	extern int EnemysImg[5];
	extern int ItemImg;
	extern int backImg[4];
	extern int swordAttackImg;
	extern int magicFireImg;
	extern int titleBackImg;
	extern int titleTextImg;
	extern int titleStageTextImg[4];
	extern int titleSelectFlame;
	extern int gameclearText;
	extern int gameoverText;
	extern int pressEnterText;
	extern int stageSelectTexts;
	extern int PlayerGaugeCoverImg;
	extern int PlayerGaugeImg;
	extern int PlayerGaugeBackImg;
	extern int EnemyDieEffect;
	extern int GetItemEffect;
	extern int MagicChargeEffect;
	extern void AllImageDelete();

	extern int TitleBGM;
	extern int GameBGMTrack[4];
	extern void AllBGMDelete();

	extern int PlayerJumpSE;
	extern int PlayerSwoadSE;
	extern int PlayerDamageSE;
	extern int PlayerHpZeroDieSE;
	extern int PlayerFallDieSE;
	extern int PlayerFireAttackSE;
	extern int EnemyDamageSE;
	extern int EnemyDieSE;
	extern int GetItemSE;
	extern int GameClearSE;
	extern int GameOverSE;

	extern void AllSEDelete();

	//������ɕ����ĉ摜��ǂݍ���
	extern void ImageLoadWave0();
	extern void ImageLoadWave1();
	extern void ImageLoadWave2();
	extern void ImageLoadWave3();
	extern void ImageLoadWave4();

	//���ʉ��̓ǂݍ���
	extern void BGMLoad();
	extern void SELoad();


}