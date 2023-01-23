#include "DxLib.h"
#include "../enemy/EnemyBase.h"
#include "../tool/ViewData.h"
#include "../map/Map.h"
#include "../scene/AddList.h"
#include "../scene/GameMgr.h"
#include "../base/Effects.h"

/*

ここには、エネミー（球状の敵）に共通する処理を記述する。
ここにある関数はオーバーライドしてはいけない

*/

void EnemyBase::finalize() {
	//nop
}

void EnemyBase::update() {

	//画面外に入るとmoveFlagがtrueに
	EnemyOnScreen();

	if (moveFlag) {
		//アニメーション更新
		animMotionUpdate();
		//当たり判定の位置更新
		UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
		//エネミー固有の動き
		EnemyOnlyMove();

		//着地していない場合、重力加速
		if (!Map::MapCheckHit((int)GetHitX(), (int)GetHitY() + (int)GetHitH(), (int)GetHitW(), 1)) {
			this->AddGravity(gravityScale);
		}
		else//着地している場合
		{
			if (GetNowSpeedY() >= 0) {
				if (Map::MapCheckHit((int)GetHitX(), (int)GetHitY() + (int)GetHitH(), (int)GetHitW(), 1)) {
					//重力リセット
					ResetNowSpeedY();
					//無敵だった場合（ヒットバック中、速度リセット）
					if (GetIncincible_Bool()) {
						ResetNowSpeedX();
						SetIncincible_Bool(false);//無敵解除
					}
					
				}
			}
		}

		//摩擦
		this->SpeedFrictionX(1.0f);

		//めり込まない移動
		this->ObjectMove(this->GetNowSpeedX(), this->GetNowSpeedY());

		//穴に落ちたら削除要請
		this->FallHoleRemove();

		//クリアしたら
		if (Game::clearJudge()) {
			//エフェクト生成
			CreateDieEffect();
			//削除要請
			SetRemoveFlag(true);
		}

	}
}


void EnemyBase::draw() {
	//画面外は描画しない
	if (GetPosX() + GetSizeW() - ViewData::GetRenderPosX() < 0) return;
	if (GetPosX() - ViewData::GetRenderPosX() > ViewData::gameSize_w) return;
	
	//キャラを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY() - ViewData::GetRenderPosY(),
		 this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH() - ViewData::GetRenderPosY(),
			this->GetPosDX(), this->GetPosDY(),
			this->GetSizeDW(), this->GetSizeDH(),
		*image, true);

	//HPバーの描画
	if (life != lifeMax) {//体力が最大値ではない場合
		//黒ボックス
		DrawBox(
			int(this->GetPosX() - ViewData::GetRenderPosX()),
			int(this->GetPosY() - 15 - ViewData::GetRenderPosY()),
			int(this->GetPosX() - ViewData::GetRenderPosX() + this->GetSizeW()),
			int(this->GetPosY() - 5 - ViewData::GetRenderPosY()),
			GetColor(0, 0, 0), true);

		//緑ボックス
		int greenBoxDrawPos = (this->GetSizeW() / lifeMax) * life;
		DrawBox(int(this->GetPosX() - ViewData::GetRenderPosX()),
			int(this->GetPosY() - 15 - ViewData::GetRenderPosY()),
			int(this->GetPosX() - ViewData::GetRenderPosX() + greenBoxDrawPos),
			int(this->GetPosY() - 5 - ViewData::GetRenderPosY()),
			GetColor(0, 255, 0), true);
	}
}

void EnemyBase::animMotionUpdate() {
	//カウント増加
	this->animCount += 1;

	int animTable[4] = {0,1,2,1};
	int moveMotionNum = sizeof(animTable) / sizeof(animTable[0]);

	//インターバルを超えたらアニメーション
	int interval = 8;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
		if (this->animNum >= moveMotionNum) {
			this->animNum = 0;
		}
	}

	//カウントを増加させ、現在のアニメーションを保存
	++angleMoveNum;
	int animChangeInterval = 10;

	//向きによって処理を更新
	//「左右→斜め→前後→斜め→最初とは反対の向き」
	switch (animAngle)
	{
	case tofront://正面
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

	case toleft://完全に左
		angleMoveNum = 0;
		saveAnimAngle = toleft;
		break;

	case toright://完全に右
		angleMoveNum = 0;
		saveAnimAngle = toright;
		break;

	case toback://後ろ
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

	case inleft://左斜め下
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

	case inright://右斜め下
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

	case outleft://左後ろ
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

	case outright://右後ろ
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


	//描画位置の設定を更新
	this->SetSrcPos((((this->animAngle / 4) * 3) + animTable[animNum]) * this->GetSizeDW(),
						((this->animAngle % 4)) * this->GetSizeDH());
}

//ヒットタイプのオブジェクトとの当たり判定が有効化された場合
void EnemyBase::HitMove(HitObjectBase& you) {

	//無敵の場合は処理を行わない
	if (GetIncincible_Bool()) { return; }

	//ノックバックのためスピードをリセット
	ResetNowSpeed();

	//当たり判定の位置によってノックバックを行う
	float youX = ViewData::GetPlayerWorldPosX();

	//「you」より左側
	if (this->GetHitX() <= youX) {
		animAngle = AnimAngle::toright;
		this->AddSpeedX(-hitBackSpeed, false);//左に移動
		this->AddSpeedY(-hitBackSpeed, true);//ジャンプ
	}
	else { //「you」より右側
		animAngle = AnimAngle::toleft;
		this->AddSpeedX(hitBackSpeed,false); //右に移動
		this->AddSpeedY(-hitBackSpeed,true); //ジャンプ
	}

	//体力減少
	AddLife(-you.GetDamage());

	//効果音
	int* seAddress;
	//体力がなくなったら
	if (LifeIsZero()) {
		//効果音のアドレス取得
		seAddress = &Loader::EnemyDieSE;
		//エフェクト生成
		CreateDieEffect();
		
		SetRemoveFlag(true); //削除
	}
	else {//体力が残っていたら
		//効果音のアドレス取得
		seAddress = &Loader::EnemyDamageSE;
	}
	//すでに同じ音が鳴っていたら止める（うるさくなるため）
	if (CheckSoundMem(*seAddress)) {
		StopSoundMem(*seAddress);
	}
	PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

	//最後に無敵状態にする(ノックバック中はヒットしてもダメージを受けない)
	SetIncincible_Bool(true);
}

//エネミーが画面内に描画されていた場合はMoveFlagをtrueにする
void EnemyBase::EnemyOnScreen() {
	
	//画面外は処理を行わない
	if (GetPosX() + GetSizeW() - ViewData::GetRenderPosX() < 0) return;
	if (GetPosX() - ViewData::GetRenderPosX() > ViewData::gameSize_w) return;

	SetMoveFlag(true);
}

void EnemyBase::FallHoleRemove() {
	if (GetPosY() > ViewData::gameSize_h) {
		//エフェクト生成
		CreateDieEffect();

		//削除要請
		SetRemoveFlag(true);
	}
}

void EnemyBase::CreateDieEffect() {
	//エフェクト生成
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