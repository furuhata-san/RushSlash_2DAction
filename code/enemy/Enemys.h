#pragma once
#include "../enemy/EnemyBase.h"

//黒い敵（横移動のみ）
class BlackEnemy : public EnemyBase {

	//今のところなし

public:
	BlackEnemy(float x, float y);
	//エネミーごとの特有の動作
	void EnemyOnlyMove() override;

	//追加したい変数は以下に
	float moveSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};


//青い敵（壁を登ってくる敵）
class BlueEnemy : public EnemyBase {

	//今のところなし

public:
	BlueEnemy(float x, float y);
	//エネミーごとの特有の動作
	void EnemyOnlyMove() override;

	//追加したい変数は以下に
	float moveSpeed;
	float climeSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};

//緑の敵（跳ねる敵）
class GreenEnemy : public EnemyBase {

	//今のところなし

public:
	GreenEnemy(float x, float y);
	//エネミーごとの特有の動作
	void EnemyOnlyMove() override;

	//追加したい変数は以下に
	float moveSpeed;
	float jumpForce;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};

//紫の敵（追いかけてくる敵）
class PurpleEnemy : public EnemyBase {

	//今のところなし

public:
	PurpleEnemy(float x, float y);
	//エネミーごとの特有の動作
	void EnemyOnlyMove() override;

	//追加したい変数は以下に
	float moveSpeed;
	float hitBackSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};


//赤い敵（落ちない敵）
class RedEnemy : public EnemyBase {

	//今のところなし

public:
	RedEnemy(float x, float y);
	//エネミーごとの特有の動作
	void EnemyOnlyMove() override;


	//追加したい変数は以下に
	float moveSpeed;

	enum MoveAngle {
		moveLeft,
		moveRight
	};
	MoveAngle moveAngle;
};