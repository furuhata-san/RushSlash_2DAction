#pragma once
#include "../base/Object.h"
#include "../scene/AddList.h"

//オブジェクト継承エフェクトクラス(インライン関数)
class Camera : public Object {

public:

	Camera();

	//向き
	enum Angle {
		non,
		left,
		right
	};
	Angle angle;

	//座標
	float posDistanceX;
	float posDistanceY;
	float moveValue;

	virtual void finalize();//終了・解放処理
	virtual void update();//更新処理
	virtual void draw();//描画処理
};
