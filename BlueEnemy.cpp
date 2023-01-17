#include "Dxlib.h"
#include "Player.h"
#include "Enemys.h"
#include "Map.h"

BlueEnemy::BlueEnemy(float x, float y) {
	//イメージロード
	this->loadImage(2);
	
	//座標設定
	SetPos(x, y);
	SetSize(64, 64);
	//描画座標を設定
	SetSrcPos(0, 0);
	SetSrcSize(32, 32);

	//最大速度の設定
	SetMaxSpeed(1, 100);
	moveSpeed = 0.1f;
	climeSpeed = 1.5f;
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
	SetLife(100);

	//無敵解除
	SetIncincible_Bool(false);

	//当たり判定作成
	CreateHitBase(GetPosX(), GetPosY(), 50, 50);
}

void BlueEnemy::EnemyOnlyMove() {

	//無敵なら処理を行わない(ノックバック中)
	if (GetIncincible_Bool()) return;

	//めり込まない移動
	if (animAngle == toleft) {
		AddSpeedX(-moveSpeed, true);
		//壁にぶつかった場合、上る
		if (Map::MapCheckHit(GetHitX() - 1, GetHitY() + GetHitH() - 1, 1, 1)) {
			ResetNowSpeed();//速度全リセット
			AddSpeedY(-climeSpeed, true);
		}
	}
	else if (animAngle == toright) {
		AddSpeedX(moveSpeed, true);
		//壁にぶつかった場合、上る
		if (Map::MapCheckHit(GetHitX() + GetHitW() + 1, GetHitY() + GetHitH() - 1, 1, 1)) {
			ResetNowSpeed();//速度全リセット
			AddSpeedY(-climeSpeed,true);
		}
	}

	//天井にぶつかった場合は方向転換
	if (Map::MapCheckHit(GetHitX(), GetHitY() - 1, GetHitW(), 1)) {
		if (animAngle == toleft) {
			ResetNowSpeedX();
			animAngle = inleft;
		}
		else if (animAngle == toright) {

			ResetNowSpeedX();
			animAngle = inright;
		}
	}

	ObjectMove(GetNowSpeedX(), GetNowSpeedY());
}
