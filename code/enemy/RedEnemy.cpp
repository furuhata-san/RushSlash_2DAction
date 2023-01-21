#include "Dxlib.h"
#include "../player/Player.h"
#include "../enemy/Enemys.h"
#include "../map/Map.h"

RedEnemy::RedEnemy(float x, float y) {
	//イメージロード
	this->loadImage(1);
	
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
	SetGravityScale(1);

	//自身のタイプとヒットタイプを設定
	SetMyType(Enemy);
	SetHitType(AttackPlayer);
	//削除フラグをfalseに
	SetRemoveFlag(false);

	//初期の方向は左
	animAngle = toright;
	moveAngle = moveLeft;

	//画面外の場合は移動を開始しない
	SetMoveFlag(false);

	//体力設定
	SetLife(70);

	//無敵解除
	SetIncincible_Bool(false);

	//当たり判定作成
	CreateHitBase(GetPosX(), GetPosY(), 50, 50);
}

void RedEnemy::EnemyOnlyMove() {

	//無敵なら処理を行わない(ノックバック中)
	if (GetIncincible_Bool()) return;

	//めり込まない移動
	if (animAngle == toleft) {
		AddSpeedX(-moveSpeed, true);
		//落ちそうになる or 壁にぶつかる　で方向転換
		if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), 1, 1)
			|| Map::MapCheckHit(GetHitX() - 2, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inleft;
		}
	}
	else if (animAngle == toright) {
		AddSpeedX(moveSpeed, true);
		//落ちそうになる or 壁にぶつかる　で方向転換
		if (!Map::MapCheckHit(GetHitX() + GetHitW(), GetHitY() + GetHitH(), 1, 1)
			|| Map::MapCheckHit(GetHitX() + GetHitW() + 1, GetHitY(), 1, 1)) {
			ResetNowSpeedX();
			animAngle = inright;
		}
	}

	ObjectMove(GetNowSpeedX(), GetNowSpeedY());
}


