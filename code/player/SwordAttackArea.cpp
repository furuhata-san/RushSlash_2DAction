#include "SwordAttackArea.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/DataLoader.h"

SwordAttackArea::SwordAttackArea(float posX, float posY, float sizeW, float sizeH, int damage) {

	image = &Loader::swordAttackImg;

	//描画座標と、画像の参照位置を設定
	SetPos(posX, posY);
	SetSize(sizeW, sizeH);
	SetSrcPos(0, 0);
	SetSrcSize(192, 192);

	animNum = 0;
	animCount = 0;
	animLimit = 10;

	//当たり判定を作成
	this->CreateHitBase(GetPosX(), GetPosY(), GetSizeW(), GetSizeH());

	//ダメージ設定
	SetDamage(damage);

	//自身のタイプを一時的に無効化
	SetMyType(Non);
	//自身のヒット対象はなし
	SetHitType(Non);

	//攻撃フレームを設定
	SettingAttackFlame(15,25);

	//現在のカウントをリセット
	ResetNowCount();

	//削除モードを無効化
	SetRemoveFlag(false);
}

void SwordAttackArea::finalize() {
	//Nop
}

void SwordAttackArea::update() {

	nowCountUp();

	//攻撃開始フレームを過ぎた場合
	if (JudgeAttackStert()) {
		//自身のタイプをプレイヤーの攻撃に
		SetMyType(AttackPlayer);
		//アニメーションを更新
		AnimationUpdate();
	}

	//攻撃フレーム終了かつ、アニメーション終了時
	if (JudgeAttackEnd()) {
		if (animNum >= animLimit) {
			SetRemoveFlag(true);//削除要請
		}
	}
}

void SwordAttackArea::draw() {
	//攻撃開始フレームが過ぎていない場合は描画しない
	if (!JudgeAttackStert()) return;

	//エフェクトをを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
		this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH(),
		this->GetPosDX(), this->GetPosDY(),
		this->GetSizeDW(), this->GetSizeDH(),
		*image, true);

	/*
	if (JudgeAttackStert()) {
		float posX = GetHitX() - ViewData::renderPosX;
		float posY = GetHitY();
		DrawBox(posX, posY ,posX + GetHitW(), posY + GetHitH(), 125, true);
	}
	*/
}

void SwordAttackArea::AnimationUpdate() {

	//カウント増加
	animCount++;

	//インターバルを超えたらアニメーション
	int interval = 1;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
	}

	//画像参照位置変更
	if (animNum < animLimit) {
		SetSrcPos((GetSizeDW() * (animNum % 5)), (GetSizeDH() * (animNum / 5)));
	}
}
