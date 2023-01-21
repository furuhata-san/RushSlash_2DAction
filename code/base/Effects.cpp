#include "../base/Effects.h"
#include "../tool/ViewData.h"

void CreateEffect(const Obj& obj) {
	Game::AddList_AddBack(obj);
}

Effect::Effect(
	int* imageAddress,
	float x,
	float y,
	float w,
	float h,
	float dx,
	float dy,
	float dw,
	float dh,
	AnimMode animMode,
	bool UI_Mode,
	bool firstDrawing,
	float playSpeed,
	int cutTotal,
	int turnNum
) {
	image = imageAddress;
	nowMode = animMode;
	SetPos(x, y);
	SetSize(w, h);
	SetSrcPos(dx, dy);
	SetSrcSize(dw, dh);
	UIMode = UI_Mode;
	drawFlag = firstDrawing;
	this->speed = playSpeed;
	imageCutTotalNum = cutTotal;
	imageTurnNum = turnNum;
	SetRemoveFlag(false);
}

void Effect::finalize() {
	//nop
}

void Effect::update() {

	//指定のモードの場合にそれぞれ処理を行う
	switch (nowMode)
	{

	case flashing:
		counter += 0.1f;
		if (counter >= speed) {//インターバルを超えたら
			drawFlag = !drawFlag;//フラグ反転
			counter = 0;//カウントリセット
		}
		break;

	case animationLoop:
		counter += speed;
		//カウントによって画像の参照位置を変更
		SetSrcPos(
			GetSizeDW() * ((int)counter % (imageCutTotalNum / (imageTurnNum + 1))),
			GetSizeDH() * ((int)counter / (imageCutTotalNum / (imageTurnNum + 1)))
		);
		break;

	case animationOnce:
		counter += speed;
		//カウントによって画像の参照位置を変更
		SetSrcPos(
			GetSizeDW() * ((int)counter % (imageCutTotalNum / (imageTurnNum + 1))),
			GetSizeDH() * ((int)counter / (imageCutTotalNum / (imageTurnNum + 1)))
		);
		//アニメーションが終了したら削除要請
		if (counter >= imageCutTotalNum) {
			SetRemoveFlag(true);
		}
		break;

	default:
		//nop
		break;
	}
}

void Effect::draw() {

	//フラグが有効なら描画
	if (drawFlag) {
		//UIではない場合はスクロール対応
		float X = GetPosX();
		if (!UIMode) {
			X -= ViewData::GetRenderPosX();
		}

		DrawRectExtendGraphF(
			X,
			GetPosY(),
			X + GetSizeW(),
			GetPosY() + GetSizeH(),
			GetPosDX(),
			GetPosDY(),
			GetSizeDW(),
			GetSizeDH(),
			*image,
			true);
	}
}