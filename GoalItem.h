#pragma once
#include "HitObjectBase.h"

class GoalItem : public HitObjectBase {

	int* image;

public:

	GoalItem(float x, float y, int colerNum);

	void finalize() override;//終了・解放処理
	void update() override;//更新処理
	void draw() override;//描画処理
	void HitMove(HitObjectBase& you) override;		//ヒットした場合の処理
};