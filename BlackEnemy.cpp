#include "Dxlib.h"
#include "Player.h"
#include "Enemys.h"
#include "Map.h"

BlackEnemy::BlackEnemy(float x, float y) {
	//イメージロード
	this->loadImage(0);

	//座標設定
	SetPos(x, y);
	SetSize(64, 64);
	//描画座標を設定
	SetSrcPos(0, 0);
	SetSrcSize(32, 32);

	//最大速度の設定
	SetMaxSpeed(1, 100);
	moveSpeed = 0.1f;
	SetHitBackSpeed(7.5f);
	ResetNowSpeed();
	SetGravityScale(0.8f);

	//自身のタイプとヒットタイプを設定
	SetMyType(Enemy);
	SetHitType(AttackPlayer);
	//削除フラグをfalseに
	SetRemoveFlag(false);

	//初期の方向は左
	animAngle = toleft;
	moveAngle = moveLeft;

	//画面外の場合は移動を開始しない
	SetMoveFlag(false);

	//体力設定
	SetLife(60);

	//無敵解除
	SetIncincible_Bool(false);

	//当たり判定作成
	CreateHitBase(GetPosX(), GetPosY(), 50, 50);
}

void BlackEnemy::EnemyOnlyMove() {

	//無敵なら処理を行わない(ノックバック中)
	if (GetIncincible_Bool()) return;

	//めり込まない移動
	if (animAngle == toleft) {
		AddSpeedX(-moveSpeed, true);
		//壁にぶつかると方向転換
		if (Map::MapCheckHit(GetHitX() - 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inleft;
		}
	}
	else if (animAngle == toright) {
		AddSpeedX(moveSpeed, true);
		//壁にぶつかると方向転換
		if (Map::MapCheckHit(GetHitX() + GetHitW() + 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inright;
		}
	}

	ObjectMove(GetNowSpeedX(), GetNowSpeedY());
}
