#pragma once

/// <summary>
/// インライン
/// </summary>

class Object {

	float x, y;	//XY座標
	float w, h;	//横幅
	int dx, dy; //描画時の横幅
	int dw, dh; //描画時の横幅

	float maxSpeedX, maxSpeedY;
	float nowSpeedX, nowSpeedY;

	bool removeSinceList;

public:
	//入力値に上書き
	virtual void SetPos(float x_, float y_);
	virtual void SetSize(float w_, float h_);
	virtual void SetSrcPos(int dx_, int dy_);
	virtual void SetSrcSize(int dw_, int dh_);
	virtual void SetMaxSpeed(float maxX, float maxY);

	//値をリセット
	virtual void ResetNowSpeed();
	virtual void ResetNowSpeedX();
	virtual void ResetNowSpeedY();

	//指定の変数の値を戻り値として受け取る
	virtual float GetPosX();
	virtual float GetPosY();
	virtual float GetSizeW();
	virtual float GetSizeH();
	virtual int GetPosDX();
	virtual int GetPosDY();
	virtual int GetSizeDW();
	virtual int GetSizeDH();
	virtual float GetNowSpeedX();
	virtual float GetNowSpeedY();

	//指定の変数に加算
	virtual void AddPosX(float value);
	virtual void AddPosY(float value);

	//加速（bool = true -> 最高速度以上なら補正）
	virtual void AddSpeedX(float value, bool adjustment);
	//加速（bool = true -> 最高速度以上なら補正）
	virtual void AddSpeedY(float value, bool adjustment);

	//速度減少
	virtual void SpeedFrictionX(float power);

	//重力
	virtual void AddGravity(float power);

	//リストから削除する場合はtrueに
	virtual void SetRemoveFlag(bool remove);
	virtual bool GetRemoveFlag();

	//追加したい関数は以下に記述


	//オーバーライド用関数（★これ以下は変更不可）
	virtual void finalize() { /*nop*/ };//終了・解放処理
	virtual void update() { /*nop*/ };//更新処理
	virtual void draw() { /*nop*/ };//描画処理
};