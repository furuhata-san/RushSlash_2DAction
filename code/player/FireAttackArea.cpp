#include "FireAttackArea.h"
#include "Dxlib.h"
#include "../tool/ViewData.h"
#include "../tool/DataLoader.h"

FireAttackArea::FireAttackArea(float posX, float posY, float sizeW, float sizeH, int damage) {

	//イメージを読み込み
	image = &Loader::magicFireImg;

	int* attackSE = &Loader::PlayerFireAttackSE;
	PlaySoundMem(*attackSE, DX_PLAYTYPE_BACK);

	//描画座標と、画像の参照位置を設定
	SetPos(posX, posY);
	SetSize(sizeW, sizeH);
	SetSrcPos(0, 0);
	SetSrcSize(640, 240);

	animNum = 0;
	animCount = 0;
	animLimit = 8;

	//当たり判定を作成（高さ半分）
	this->CreateHitBase(GetPosX(), GetPosY() + (GetSizeH() / 2), GetSizeW(), GetSizeH() / 2);

	//ダメージ設定
	SetDamage(damage);

	//自身のタイプを一時的に無効化
	SetMyType(Non);
	//自身のヒット対象はなし
	SetHitType(Non);

	//攻撃フレームを設定
	SettingAttackFlame(4 * 2, 4 * (animLimit - 2));

	//現在のカウントをリセット
	ResetNowCount();

	//削除モードを無効化
	SetRemoveFlag(false);
}

void FireAttackArea::finalize() {
	//Nop
}

void FireAttackArea::update() {

	nowCountUp();

	//アニメーション更新
	AnimationUpdate();

	//攻撃開始フレームを過ぎた場合
	if (JudgeAttackStert()) {
		//自身のタイプをプレイヤーの攻撃に
		SetMyType(AttackPlayer);
	}

	//攻撃フレーム終了かつ、アニメーション終了時
	if (JudgeAttackEnd()) {
		if (animNum >= animLimit - 2) {
			SetRemoveFlag(true);//削除要請
		}
	}


}

void FireAttackArea::draw() {
	
	//エフェクトをを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
		this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH(),
		this->GetPosDX(), this->GetPosDY(),
		this->GetSizeDW(), this->GetSizeDH(),
		*image, true);
}

void FireAttackArea::AnimationUpdate() {
	
	//カウント増加
	animCount++;

	//インターバルを超えたらアニメーション
	int interval = 3;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
	}

	//画像参照位置変更
	if (animNum < animLimit) {
		SetSrcPos(0, GetSizeDH() * animNum);
	}
}
