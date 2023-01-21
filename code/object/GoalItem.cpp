#include "Dxlib.h"
#include "../player/Player.h"
#include "GoalItem.h"
#include "../tool/ViewData.h"
#include "../tool/DataLoader.h"
#include "../map/Map.h"
#include "../scene/SceneMgr.h"
#include "../base/Effects.h"
#include "../scene/AddList.h"

GoalItem::GoalItem(float x, float y, int colorNum) {
	//画像読み込み（保存領域から）
	image = &Loader::ItemImg;

	//座標の初期化
	SetPos(x, y + ((64 - 44) / 2));
	SetSize(64, 44);

	//描画位置の初期化
	SetSrcPos(32 * colorNum, 0);
	SetSrcSize(32, 22);

	ResetNowSpeed();

	//自身のタイプとヒットタイプを設定
	SetHitType(HitObjectType::Player);
	SetMyType(HitObjectType::Item);

	//削除しない
	SetRemoveFlag(false);

	//当たり判定作成
	CreateHitBase(this->GetPosX(), this->GetPosY(), GetSizeW(), GetSizeH());//自身の当たり判定
}

void GoalItem::finalize() {
	//Nop
}

void GoalItem::update() {

}

void GoalItem::draw() {
	//描画位置の設定を更新
	DrawRectExtendGraphF
	(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
		this->GetPosX() + this->GetSizeW() - ViewData::GetRenderPosX(), this->GetPosY() + this->GetSizeH(),
		this->GetPosDX(), this->GetPosDY(),
		this->GetSizeDW(), this->GetSizeDH(),
		*image, true);
}

void GoalItem::HitMove(HitObjectBase& you) {

	//効果音を鳴らす
	int* seAddress = &Loader::GetItemSE;
	PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

	//エフェクト生成
	float sizeW = 100.0f;
	float sizeH = 100.0f;
	Obj createObj =
		Obj(new Effect(
			&Loader::GetItemEffect,
			this->GetPosX() - (sizeW / 2) + (this->GetSizeW() / 2),
			this->GetPosY() - (sizeH / 2) + (this->GetSizeH() / 2),
			sizeW,
			sizeH,
			0.0f,
			0.0f,
			200.0f,
			200.0f,
			Effect::AnimMode::animationOnce,
			false,
			true,
			1.5f,
			30,
			6
		));
	CreateEffect(createObj);
	SetRemoveFlag(true);

	//削除
	SetRemoveFlag(true);

}