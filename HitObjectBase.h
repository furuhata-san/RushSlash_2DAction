#pragma once
#include "DxLib.h"
#include "Object.h"

class HitObjectBase : public Object {

public:
	enum HitObjectType {
		AllHit,//動かさない　すべてのヒットオブジェクトと当たり判定を行う

		//追加したい場合は以下////////////////////////////////////////////////////
		Player,
		Enemy,
		AttackPlayer,
		Item,

		//ここまで////////////////////////////////////////////////////////////////

		Non//動かさない　すべてのヒットオブジェクトと当たり判定を行わない
		//以下への追加は禁止
	};

private:

	//当たり判定の隅の座標
	float hitX, hitY;
	float hitW, hitH;
	HitObjectType myType;
	HitObjectType hitType;

	int invincibleCounter;//直接参照禁止
	int invincibleTime;//直接参照禁止
	bool invincibleFlag;//直接参照禁止

	int damage;//直接参照禁止

public:

	HitObjectBase() {};

	//共有する関数のみを記述
	virtual bool HitJudge(HitObjectBase& you);//指定オブジェクトとヒットしているか

	virtual void SetMyType(HitObjectType type);//自身のタイプ
	virtual HitObjectType GetMyType();
	virtual void SetHitType(HitObjectType type);//当たり判定を行うタイプ
	virtual HitObjectType GetHitType();

	virtual void HitMove(HitObjectBase& you){/*nop*/ };

	virtual void SetDamage(int value);//このオブジェクトがヒットしたオブジェクトに与えるダメージ量を設定
	virtual int GetDamage();//このオブジェクトが持つダメージを戻り値として得る

	virtual void CreateHitBase(float x, float y, float w, float h);

	virtual void UpdateHitBase(float posX, float posY);

	virtual void ObjectMove(float preX, float preY);//めり込まない移動

	//無敵状態のリセット
	virtual void InvincibleInitialize_Time(int time);//無敵時間の初期設定
	virtual void SetIncincible_Time();//無敵起動
	virtual bool GetIncincible_Time();//内部カウントが無敵時間を超えていたら無敵を無効化

	virtual int GetIncincible_Count();
	virtual void SetIncincible_Bool(bool value);
	virtual bool GetIncincible_Bool();


	virtual float GetHitX();//このオブジェクトの当たり判定（X座標）
	virtual float GetHitY();//このオブジェクトの当たり判定（Y座標）
	virtual float GetHitW();//このオブジェクトの当たり判定（横幅）
	virtual float GetHitH();//このオブジェクトの当たり判定（縦幅）
};