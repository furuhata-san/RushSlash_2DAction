#pragma once
#include "AttackArea.h"

class SwordAttackArea : public AttackArea {

	int* image;
	int animNum;	//現在表示しているイメージ番号
	int animCount;	//描画時アニメーションカウント
	int animLimit;

public:
	SwordAttackArea(float posX, float posY, float sizeW, float sizeH, int damage);

	void finalize() override;//終了・解放処理
	void update() override;//更新処理
	void draw() override;//描画処理
	void AnimationUpdate();	//描画更新
};