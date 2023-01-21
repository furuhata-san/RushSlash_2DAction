#pragma once
#include "../base/Object.h"
#include "../scene/AddList.h"

//エフェクト生成用関数
extern void CreateEffect(const Obj& obj);

//オブジェクト継承エフェクトクラス(インライン関数)
class Effect : public Object {

	int* image;
	float speed;
	float counter;
	bool drawFlag;
	bool UIMode;

	int imageCutTotalNum;
	int imageTurnNum;


public:

	enum AnimMode {
		normal,
		flashing,
		animationLoop,
		animationOnce,
	};
	AnimMode nowMode;

	Effect(
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
		bool firstDrawing = true,
		float playSpeed = 0,
		int cutTotal = 0, 
		int turnNum = 0
	);

	virtual void finalize();//終了・解放処理
	virtual void update();//更新処理
	virtual void draw();//描画処理

};
