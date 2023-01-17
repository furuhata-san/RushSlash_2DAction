#pragma once

/// <summary>
/// 
/// 画像をWaveごとに分けて読み込み、
/// 終了時に全開放することとする。
/// 
/// ここにあるデータはポインタで参照し、
/// 画像のコピー等は禁止とする。
/// 
/// cppに読み込む順番を記載すること。
/// 
/// また、シーンごとに読み込みたい画像等がある場合は、
/// シーンクラスで読み込みを行う。
/// 
/// また、ここにある関数はプロジェクト全体で
/// 一回だけしか呼んではならない。
/// （ウェーブの呼び出す順番ははバラバラでも可）
/// </summary>

namespace Loader {

	//画像の保存領域を宣言
	//宣言した後は変数の実体を宣言し、cpp内の削除コードに追加
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

	//複数回に分けて画像を読み込み
	extern void ImageLoadWave0();
	extern void ImageLoadWave1();
	extern void ImageLoadWave2();
	extern void ImageLoadWave3();
	extern void ImageLoadWave4();

	//効果音の読み込み
	extern void BGMLoad();
	extern void SELoad();


}