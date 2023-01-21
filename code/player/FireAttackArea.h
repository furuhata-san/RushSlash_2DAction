#pragma once
#pragma once
#include "AttackArea.h"

class FireAttackArea : public AttackArea {

	int* image;

public:
	FireAttackArea(float posX, float posY, float sizeW, float sizeH, int damage);

	void finalize() override;//終了・解放処理
	void update() override;//更新処理
	void draw() override;//描画処理
	void AnimationUpdate();	//描画更新
};