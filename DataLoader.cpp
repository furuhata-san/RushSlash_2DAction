#include"DxLib.h"
#include"DataLoader.h"
#include "string"

namespace Loader {

	//�����̏����͌�ŃR���e�i���ɕύX����
	//�������Ɏ��̂�錾����B
	
	//�摜=================================================================
	int playerImg;
	int mapBlockImg;
	int EnemysImg[5];
	int ItemImg;
	int backImg[4];
	int swordAttackImg;
	int magicFireImg;
	int titleBackImg;
	int titleTextImg;
	int titleStageTextImg[4];
	int titleSelectFlame;
	int gameclearText;
	int gameoverText;
	int pressEnterText;
	int stageSelectTexts;
	int PlayerGaugeCoverImg;
	int PlayerGaugeImg;
	int PlayerGaugeBackImg;
	int EnemyDieEffect;
	int GetItemEffect;
	int MagicChargeEffect;

	//�����̐錾��A�����ɉ���̏������L�q
	void AllImageDelete() {
		DeleteGraph(playerImg);
		DeleteGraph(mapBlockImg);
		for (int i = 0; i < sizeof(EnemysImg) / sizeof(EnemysImg[0]); ++i) {
			DeleteGraph(EnemysImg[i]);
		}
		for (int i = 0; i < sizeof(backImg) / sizeof(backImg[0]); ++i) {
			DeleteGraph(backImg[i]);
		}
		DeleteGraph(ItemImg);
		DeleteGraph(swordAttackImg);
		DeleteGraph(magicFireImg);
		DeleteGraph(titleBackImg);
		DeleteGraph(titleTextImg);
		DeleteGraph(gameclearText);
		DeleteGraph(gameoverText);
		DeleteGraph(pressEnterText);
		DeleteGraph(stageSelectTexts);
		for (int i = 0; i < sizeof(titleStageTextImg) / sizeof(titleStageTextImg[0]); ++i) {
			DeleteGraph(titleStageTextImg[i]);
		}
		DeleteGraph(titleSelectFlame);
		DeleteGraph(PlayerGaugeCoverImg);
		DeleteGraph(PlayerGaugeImg);
		DeleteGraph(PlayerGaugeBackImg);
		DeleteGraph(EnemyDieEffect);
		DeleteGraph(GetItemEffect);
		DeleteGraph(MagicChargeEffect);
	}

	void ImageLoadWave0() {
		//�ǂݍ��ނ���
		//�^�C�g�����S
		//�^�C�g���w�i
		//�^�C�g���X�e�[�W�Z���N�g
		//�^�C�g���I���t���[��
		//�v���C���[�X�v���C�g
		titleBackImg = LoadGraph("./data/mapImage/TitleBackGround.png");
		titleTextImg = LoadGraph("./data/textImage/TitleLogo.png");
		titleStageTextImg[0] = LoadGraph("./data/textImage/StageMorning.png");
		titleStageTextImg[1] = LoadGraph("./data/textImage/StageEvening.png");
		titleStageTextImg[2] = LoadGraph("./data/textImage/StageMidnight.png");
		titleStageTextImg[3] = LoadGraph("./data/textImage/StageEndless.png");
		titleSelectFlame = LoadGraph("./data/mapImage/MapSelectFlame.png");
		playerImg = LoadGraph("./data/charaImage/PlayerSprite.png");
	}
	void ImageLoadWave1() {
		//�ǂݍ��ނ���
		//���[�h���
		//�X�e�[�W�Z���N�g����
		//�w�i4���
		backImg[0] = LoadGraph("./data/mapImage/MapBackGroundM.jpg");
		backImg[1] = LoadGraph("./data/mapImage/MapBackGroundA.jpg");
		backImg[2] = LoadGraph("./data/mapImage/MapBackGroundN.jpg");
		backImg[3] = LoadGraph("./data/mapImage/MapBackGroundBoss.jpg");
		stageSelectTexts = LoadGraph("./data/textImage/StageSelect.png");
	}
	void ImageLoadWave2() {
		//�ǂݍ��ނ���
		//�Q�[�������i�N���A�E�I�[�o�[�E�G���^�[�L�[�j
		//����
		ItemImg = LoadGraph("./data/mapImage/Item.png");
		gameclearText = LoadGraph("./data/textImage/StageClear.png");
		gameoverText = LoadGraph("./data/textImage/GameOver.png");;
		pressEnterText = LoadGraph("./data/textImage/EnterKey.png");;
	}
	void ImageLoadWave3() {
		//�ǂݍ��ނ���
		//�}�b�v�u���b�N
		//�G�l�~�[�X�v���C�g
		mapBlockImg = LoadGraph("./data/mapImage/MapBlock.png");
		EnemysImg[0] = LoadGraph("./data/charaImage/BlackEnemy.png");
		EnemysImg[1] = LoadGraph("./data/charaImage/RedEnemy.png");
		EnemysImg[2] = LoadGraph("./data/charaImage/BlueEnemy.png");
		EnemysImg[3] = LoadGraph("./data/charaImage/GreenEnemy.png");
		EnemysImg[4] = LoadGraph("./data/charaImage/PurpleEnemy.png");
	}
	void ImageLoadWave4() {
		//�ǂݍ��ނ���
		//���U���G�t�F�N�g
		//���̖��@�U��
		//�v���C���[UI
		//�G���S�G�t�F�N�g
		//�A�C�e���l���G�t�F�N�g
		//���@�G�t�F�N�g
		swordAttackImg = LoadGraph("./data/effectImage/PlayerAttack.png");
		magicFireImg = LoadGraph("./data/effectImage/PlayerFire.png");
		PlayerGaugeCoverImg = LoadGraph("./data/charaImage/LifeGaugeCover.png");
		PlayerGaugeImg = LoadGraph("./data/charaImage/LifeGauge.png");
		PlayerGaugeBackImg = LoadGraph("./data/charaImage/LifeGaugeBack.png");
		EnemyDieEffect = LoadGraph("./data/effectImage/EnemyDieEffect.png");
		GetItemEffect = LoadGraph("./data/effectImage/GetItemEffect.png");
		MagicChargeEffect = LoadGraph("./data/effectImage/FireMagicCharge.png");
	}

	//BGM=================================================================
	int TitleBGM;
	int GameBGMTrack[4];
	void AllBGMDelete() {
		DeleteSoundMem(TitleBGM);
		for (int i = 0; i < sizeof(GameBGMTrack) / sizeof(GameBGMTrack[0]); ++i) {
			DeleteSoundMem(GameBGMTrack[i]);
		}
	}

	void BGMLoad() {
		TitleBGM = LoadSoundMem("./data/bgm/TitleBGM.mp3");
		GameBGMTrack[0] = LoadSoundMem("./data/bgm/MorningBGM.mp3");
		GameBGMTrack[1] = LoadSoundMem("./data/bgm/EveningBGM.mp3");
		GameBGMTrack[2] = LoadSoundMem("./data/bgm/MidnightBGM.mp3");
		GameBGMTrack[3] = LoadSoundMem("./data/bgm/DreamBGM.mp3");
	}



	//���ʉ�=================================================================
	int PlayerJumpSE;
	int PlayerSwoadSE;
	int PlayerDamageSE;
	int PlayerHpZeroDieSE;
	int PlayerFallDieSE;
	int PlayerFireAttackSE;
	int EnemyDamageSE;
	int EnemyDieSE;
	int GetItemSE;
	int GameClearSE;
	int GameOverSE;
	void AllSEDelete() {
		DeleteSoundMem(PlayerJumpSE);
		DeleteSoundMem(PlayerSwoadSE);
		DeleteSoundMem(PlayerDamageSE);
		DeleteSoundMem(PlayerHpZeroDieSE);
		DeleteSoundMem(PlayerFallDieSE);
		DeleteSoundMem(PlayerFireAttackSE);
		DeleteSoundMem(EnemyDamageSE);
		DeleteSoundMem(EnemyDieSE);
		DeleteSoundMem(GetItemSE);
		DeleteSoundMem(GameClearSE);
		DeleteSoundMem(GameOverSE);
	}

	void SELoad() {
		PlayerJumpSE = LoadSoundMem("./data/se/PlayerJump.mp3");
		PlayerSwoadSE = LoadSoundMem("./data/se/PlayerSword.mp3");
		PlayerDamageSE = LoadSoundMem("./data/se/PlayerDamage.mp3");
		PlayerHpZeroDieSE = LoadSoundMem("./data/se/PlayerHpZeroDie.mp3");
		PlayerFallDieSE = LoadSoundMem("./data/se/PlayerFallDie.mp3");
		PlayerFireAttackSE = LoadSoundMem("./data/se/FireAttack.mp3");
		EnemyDamageSE = LoadSoundMem("./data/se/EnemyDamage.mp3");
		EnemyDieSE = LoadSoundMem("./data/se/EnemyDie.mp3");
		GetItemSE = LoadSoundMem("./data/se/GetItem.mp3");
		GameClearSE = LoadSoundMem("./data/se/GameClearSE.mp3");
		GameOverSE = LoadSoundMem("./data/se/GameOverSE.mp3");
		ChangeVolumeSoundMem(255 * 80 / 100, GameOverSE);
	}
}

