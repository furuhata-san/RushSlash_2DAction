#pragma once
#include "Dxlib.h"
#include "HitObjectBase.h"
#include "DataLoader.h"
#include "ViewData.h"

class EnemyBase : public HitObjectBase {

	int* image;
	int animNum;
	int animCount;
	int enemyType;
	int angleMoveNum;

	int life;
	int lifeMax;

	bool moveFlag;//動くかどうか

	float hitBackSpeed;
	float gravityScale;

public:

	//イメージ読み込み
	void loadImage(int EnemyType) { image = &Loader::EnemysImg[EnemyType]; };

	//ヒットした場合の処理
	void SetHitBackSpeed(float speed) { hitBackSpeed = speed; }
	void HitMove(HitObjectBase& you);

	void SetMoveFlag(bool value) { moveFlag = value; }
	bool GetMoveFlag() { return moveFlag; }
	void EnemyOnScreen();

	void finalize() override;//終了・解放処理
	void update() override;//更新処理
	void draw() override;//描画処理

	//エネミーごとの固有の動き
	virtual void EnemyOnlyMove(){/*Nop*/};

	//追加する変数は以下に
	void SetLife(int value) { lifeMax = value;  life = value; }
	void AddLife(int value) { life += value; }
	int GetLife() { return life; }
	bool LifeIsZero() { return life <= 0; }
	void SetGravityScale(float value) { gravityScale = value; };

	//アニメーション
	enum AnimAngle {
		tofront,
		toleft,
		toright,
		toback,
		inleft,
		inright,
		outleft,
		outright,

		Non
	};
	AnimAngle animAngle;
	AnimAngle saveAnimAngle;
	void animMotionUpdate();
	void animCounterReset() { animCount = 0; animNum = 0; }
	int GetAnimNum() { return animNum; }
	void FallHoleRemove();
	void CreateDieEffect();
};