#pragma once
#include "../base/HitObjectBase.h"
#include "../scene/AddList.h"

class Player : public HitObjectBase {

	int* image;
	int animNum;
	int animCount;
	int saveHitW, saveHitH;
	int magicChargeValue;
	bool GameResultFlag;

public:
	
	Player(float posX, float posY);//コンストラクタ
	void finalize() override;//終了・解放処理
	void update() override;//更新処理
	void draw() override;//描画処理
	void HitMove(HitObjectBase& you) override;		//ヒットした場合の処理

	//追加する変数は以下に
	
	//アニメーション
	enum Motion {
		idle,
		sword,
		magic,
		win,
		run,
		jump,
		damage,
		die
	};
	Motion motion;

	void animMotionUpdate();
	void animCounterReset() { animCount = 0; animNum = 0; }
	int GetAnimNum() { return animNum; }
	bool imageNullChecker(int num) { return num <= (int)Motion::run; }

	//移動
	enum Angle {
		left,
		right
	};
	Angle angle;
	float runForce;
	float jumpForce;

	//体力
	int hp;
	int hpMax;

	//動作変更
	void MotionUpdate(Motion& nowMotion);
	void PlayMotion(Motion nowMotion);
	void PlayerFallHole();
	void PlayerGameClear();
	Motion MotionChange(const Motion nowMotion, bool action);

	void DrawLifeGaugeUI();

	void CraeteAttackArea(hObj& hobj);
};