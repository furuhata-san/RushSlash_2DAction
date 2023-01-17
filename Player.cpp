#include "Dxlib.h"
#include <time.h>
#include "Player.h"
#include "KeyChecker.h"
#include "SceneMgr.h"
#include "DataLoader.h"
#include "Map.h"
#include "ViewData.h"
#include "GameMgr.h"
//攻撃エリア
#include "SwordAttackArea.h"
#include "FireAttackArea.h"
#include "Effects.h"

//コンストラクタ　実体化時に行われる処理
Player::Player(float posX, float posY) {
	//画像読み込み（保存領域から）
	image = &Loader::playerImg;

	//座標の初期化
	SetPos(posX, posY);
	SetSize(140, 140);

	//描画位置の初期化
	SetSrcPos(0, 0);
	SetSrcSize(140, 140);

	//移動速度の設定
	SetMaxSpeed(20, 100);
	runForce = 8.5f;
	jumpForce = 20.5f;
	ResetNowSpeed();

	//体力の設定
	hpMax = 10;
	hp = hpMax;

	//リザルト表示時に使用
	GameResultFlag = true;

	//アニメーションカウントをリセット
	animCounterReset();

	//自身のタイプとヒットタイプを設定
	SetHitType(HitObjectType::AllHit);
	SetMyType(HitObjectType::Player);

	//最初のモーションを設定
	this->motion = Motion::idle;
	this->angle = Angle::right;

	//削除しない
	SetRemoveFlag(false);

	InvincibleInitialize_Time(90);//無敵時間初期化

	//当たり判定作成
	CreateHitBase(this->GetPosX(), this->GetPosY(), 60, 100);//自身の当たり判定
}

//終了
void Player::finalize() {
	//音を止める
	int* dieSE = &Loader::PlayerFallDieSE;
	StopSoundMem(*dieSE);
	int* OverSE = &Loader::GameOverSE;
	StopSoundMem(*OverSE);
	int* ClearSE = &Loader::GameClearSE;
	StopSoundMem(*ClearSE);
}

//更新
void Player::update() {
	
	//入力によりモーション更新
	MotionUpdate(this->motion);

	//モーションにより処理更新
	PlayMotion(this->motion);

	//アニメーション情報全般の更新
	animMotionUpdate();

	PlayerGameClear();

	//当たり判定の位置更新
	UpdateHitBase(this->GetPosX() + ((this->GetSizeW() - this->GetHitW()) / 2), this->GetPosY() + ((this->GetSizeH() - this->GetHitH()) / 2));
}

//描画
void Player::draw() {

	//アングルが向きの場合は描画を反転
	bool mirrorFlag = false;
	if (this->angle == Angle::left) mirrorFlag = true;

	//無敵ではない場合（＝通常描画）　もしくは　無敵時カウントが一定数たまっている場合（＝点滅する）
	if (!GetIncincible_Time() || GetIncincible_Count() % 5 == 0) {
		//キャラを描画（この式を行うことで読み込む画像が一枚で済む）
		//スクロール対応済み
		DrawRectGraphF(this->GetPosX() - ViewData::GetRenderPosX(), this->GetPosY(),
			this->GetPosDX(), this->GetPosDY(),
			this->GetSizeDW(), this->GetSizeDH(),
			*image, TRUE, mirrorFlag);
	}

	//ライフゲージ描画
	DrawLifeGaugeUI();
}

void Player::MotionUpdate(Motion& nowMotion) {
	
	//ここでは、プレイヤーのモーションごとに、
	//入力を受け取り、モーションをチェンジする
	//ケースごとに処理を入力

	switch (nowMotion) {

		//優先度の高い順に記載

	case idle:
		//地面がない場合は落下状態へ
		if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
			MotionChange(Motion::jump, false);
		}
		//ジャンプ([W][UP])
		else if (KeyChecker::InputDown(KEY_INPUT_W) || KeyChecker::InputDown(KEY_INPUT_UP)) {
			MotionChange(Motion::jump, true);
		}
		//剣で攻撃([J][Z])
		else if (KeyChecker::InputDown(KEY_INPUT_J) || KeyChecker::InputDown(KEY_INPUT_Z)) {
			MotionChange(Motion::sword, true);
		}
		//魔法を使う([K][X])
		else if (KeyChecker::InputDown(KEY_INPUT_K) || KeyChecker::InputDown(KEY_INPUT_X)) {
			MotionChange(Motion::magic, true);
		}
		//移動キーの入力で移動状態へ([A][D][Left][Right])
		else if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) { 
			MotionChange(Motion::run, true);
		}
		else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
			MotionChange(Motion::run, true);
		}
		break;

	case sword:
		//アニメーション終了時　待機状態へ
		if (animNum >= 3) {
			MotionChange(Motion::idle, false);
		}
		break;

	case magic:
		//魔法をためる
		if (magicChargeValue <= 640) {
			//指定回数毎にエフェクト生成
			if (magicChargeValue % 100 == 0) {
				//エフェクト生成
				float sizeW = 250.0f;
				float sizeH = 250.0f;
				Obj createObj =
					Obj(new Effect(
						&Loader::MagicChargeEffect,
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
						1.0f,
						30,
						5
					));
				CreateEffect(createObj);
			}

			//カウントアップ
			magicChargeValue += 10;
		}

		//キー入力がなくなった時　待機状態へ変更し、タイミングによって魔法を発動
		if (!KeyChecker::InputOn(KEY_INPUT_K) && !KeyChecker::InputOn(KEY_INPUT_X)) {

			//炎の魔法
			float areaSizeW = magicChargeValue;
			float areaSizeH = 240;
			float areaPosX = GetHitX() - ((areaSizeW - GetHitW()) / 2);
			float areaPosY = GetHitY() - (areaSizeH / 2);
			int damageValue = magicChargeValue / 10;

			hObj object(new FireAttackArea(areaPosX, areaPosY, areaSizeW, areaSizeH, damageValue));
			CraeteAttackArea(object);

			MotionChange(Motion::idle, false);

			//魔法のためを０に
			magicChargeValue = 0;
		}
		break;

	case win:
		break;

	case run:
		//移動キーが入力されていた場合は向きを設定
		if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
			angle = Angle::left;
		}
		else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
			angle = Angle::right;
		}
		else {//押されていない場合は、待機状態へ
			MotionChange(Motion::idle, false);
		}

		//地面がない場合は落下状態へ
		if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
			MotionChange(Motion::jump, false);
		}
		//ジャンプ([W][UP])
		else if (KeyChecker::InputDown(KEY_INPUT_W) || KeyChecker::InputDown(KEY_INPUT_UP)) {
			MotionChange(Motion::jump, true);
		}
		//剣で攻撃([J][Z])
		else if (KeyChecker::InputDown(KEY_INPUT_J) || KeyChecker::InputDown(KEY_INPUT_Z)) {
			MotionChange(Motion::sword, true);
		}
		//魔法を使う([K][X])
		else if (KeyChecker::InputDown(KEY_INPUT_K) || KeyChecker::InputDown(KEY_INPUT_X)) {
			MotionChange(Motion::magic, true);
		}
		break;

	case jump:
		//着地したら待機状態へ
		if (Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
			MotionChange(Motion::idle, false);
		}
		//頭がぶつかったら速度リセット
		else if (Map::MapCheckHit(GetHitX(), GetHitY() - 1, GetHitW(), 1)) {
			this->ResetNowSpeedY();
		}

		break;

	case damage:
		//着地したら状態を変更へ
		if (GetNowSpeedY() >= 0) {
			if (Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
				if (hp > 0) {//体力が残っている場合
					SetIncincible_Time();//無敵になる
					MotionChange(Motion::idle, false);//待機状態へ
				}
				else{//体力が残っていない場合
					MotionChange(Motion::die, false);//死亡状態へ
				}
			}
		}
		break;

	case die:
		break;
	}

	//魔法チャージ中ではない場合
	if (nowMotion != magic) {
		//チャージ量リセット
		magicChargeValue = 0;
	}


	//落下判定
	PlayerFallHole();
}

//次のモーションと、アクションを行うかどうか
Player::Motion Player::MotionChange(const Motion chengeotion, bool action) {
	//この関数（MotionChenge）が呼ばれた場合、
	//引数によって処理を行う

	int* nowSoundMem = 0; //効果音のポインタ

	if (action) {//アクションを行う場合は、処理を行う
		switch (chengeotion) {
		case idle:
			break;

		case sword:
		{
			motion = Motion::sword;	//剣攻撃状態へ変更
			animCounterReset();	//アニメーションを一度リセット

			//攻撃判定を作成
			float swordAreaW = 150;
			float swordAreaH = 150;

			//向きによって場所を調整
			float areaPosX;
			if (angle == left) {
				areaPosX = GetHitX() - (swordAreaW);
			}
			else {
				areaPosX = GetHitX() + GetHitW();
			}
			float areaPosY = GetPosY() - ((swordAreaH - GetHitH()) / 2);

			hObj object(new SwordAttackArea(areaPosX, areaPosY, swordAreaW, swordAreaH, 30));
			CraeteAttackArea(object);

			nowSoundMem = &Loader::PlayerSwoadSE;//効果音のアドレスを渡す
		}
			break;

		case magic:
			animCounterReset();
			break;

		case win:
			break;

		case run:
			if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
				angle = Angle::left;
			}
			else if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
				angle = Angle::right;
			}
			break;

		case jump:
			//速度リセットー＞加速
			this->ResetNowSpeedY();
			this->AddSpeedY(-jumpForce,true);
			nowSoundMem = &Loader::PlayerJumpSE;//効果音のアドレスを渡す
			break;

		case damage:
			this->AddSpeedY(-jumpForce / 2, true);	//ノックバック
			if (hp > 0) {//死んでいない場合
				nowSoundMem = &Loader::PlayerDamageSE;//効果音のアドレスを渡す
			}
			else {//死んだ場合
				nowSoundMem = &Loader::PlayerHpZeroDieSE;//効果音のアドレスを渡す
			}
			break;

		case die:
			nowSoundMem = &Loader::PlayerFallDieSE;//効果音のアドレスを渡す
			break;
		}
	}

	//アドレスが読み込まれている場合
	if (nowSoundMem != 0) {
		int playSound = *nowSoundMem;
		//効果音を鳴らす
		PlaySoundMem(playSound, DX_PLAYTYPE_BACK);
	}
	
	//モーション変更
	return motion = chengeotion;
}


void Player::PlayMotion(Motion nowMotion) {

	//ここでは、モーションごとのプレイヤの処理を記述する

	//ケースごとに処理を入力
	switch (nowMotion) {
	case idle:
		break;

	case sword:

		break;

	case magic:
		break;

	case win:

		if (GameResultFlag) {
			//BGMを止める
			int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
			StopSoundMem(*bgmAddress);

			//文字作成(GameClear, PressEnter)
			//Clear
			Obj createObj =
				Obj(new Effect(
					&Loader::gameclearText,
					(ViewData::size_w / 2) - (543.0f / 2 * 2),
					250.0f,
					543.0f * 2,
					114.0f * 2,
					0.0f,
					0.0f,
					543.0f,
					114.0f,
					Effect::AnimMode::normal,
					true
				));
			CreateEffect(createObj);

			//Enter
			createObj =
				Obj(new Effect(
					&Loader::pressEnterText,
					(ViewData::size_w / 2) - (590.0f / 2),
					550.0f,
					590.0f,
					107.0f,
					0.0f,
					0.0f,
					590.0f,
					107.0f,
					Effect::AnimMode::flashing,
					true,
					true,
					3.0f
				));
			CreateEffect(createObj);

			//ゲームオーバー効果音
			int* seAddress = &Loader::GameClearSE;

			PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

			//フラグをオフに
			GameResultFlag = false;
		}

		if (KeyChecker::InputUp(KEY_INPUT_RETURN)) {
			ChengeScene(new TitleScene);
		}
		break;

	case run:
		//向いている方向によって加速する
		if (angle == right) {
			this->AddSpeedX(runForce, true);
		}
		else {
			this->AddSpeedX(-runForce, true);
		}
		break;

	case jump:
		//キー入力方向へ移動
		if (KeyChecker::InputOn(KEY_INPUT_D) || KeyChecker::InputOn(KEY_INPUT_RIGHT)) {
			this->AddSpeedX(runForce / 1.5f, true);
		}
		else if (KeyChecker::InputOn(KEY_INPUT_A) || KeyChecker::InputOn(KEY_INPUT_LEFT)) {
			this->AddSpeedX(-runForce / 1.5f, true);
		}

		break;

	case damage:
		//向いている方向の逆方向に加速する
		if (angle == right) {
			this->AddSpeedX(-runForce / 2, true);
		}
		else {
			this->AddSpeedX(runForce / 2, true);
		}
		break;

	case die:
		this->ResetNowSpeed();

		if (GameResultFlag) {
			//BGMを止める
			int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
			StopSoundMem(*bgmAddress);

			//文字作成(GameOver, PressEnter)
			//Over
			Obj createObj =
				Obj(new Effect(
					&Loader::gameoverText,
					(ViewData::size_w / 2) - (430 / 2 * 2),
					200.0f,
					430.0f * 2,
					128.0f * 2,
					0.0f,
					0.0f,
					430.0f,
					127.0f,
					Effect::AnimMode::normal,
					true
				));
			CreateEffect(createObj);

			//Enter
			createObj =
				Obj(new Effect(
					&Loader::pressEnterText,
					(ViewData::size_w / 2) - (590.0f / 2),
					500.0f,
					590.0f,
					107.0f,
					0.0f,
					0.0f,
					590.0f,
					107.0f,
					Effect::AnimMode::flashing,
					true,
					true,
					3.0f
				));
			CreateEffect(createObj);

			//ゲームオーバー効果音
			int* seAddress = &Loader::GameOverSE;

			PlaySoundMem(*seAddress, DX_PLAYTYPE_BACK);

			//フラグをオフに
			GameResultFlag = false;
		}

		if (KeyChecker::InputUp(KEY_INPUT_RETURN)) {
			ChengeScene(new TitleScene);
		}

		break;
	}

	//常に動作する効果

	//摩擦
	this->SpeedFrictionX(2.0f);

	//重力加速
	if (!Map::MapCheckHit(GetHitX(), GetHitY() + GetHitH(), GetHitW(), 1)) {
		this->AddGravity(1.0f);
	}

	//接地が確定している際、重力計算をリセット
	if (motion == Motion::idle || motion == Motion::run) {
		this->ResetNowSpeedY();
	}

	//めり込まない移動
	this->ObjectMove(this->GetNowSpeedX(), this->GetNowSpeedY());
}

//プレイヤーが穴に落ちたかどうかを判断し、処理を行う
void Player::PlayerFallHole() {

	//死亡している場合、処理を行わない
	if (motion == Motion::die)return;

	//プレイヤのY座標がスクリーン外だった場合
	if (this->GetPosY() > ViewData::size_h) {
		MotionChange(Motion::die, true);
	}
}

void Player::animMotionUpdate() {

	if (!this->imageNullChecker(motion)) {
		animNum = 0;
		this->SetSrcPos(this->animNum * this->GetSizeDW(), this->motion * this->GetSizeDH());
		return;
	}

	//カウント増加
	this->animCount += 1;
	int moveMotionNum = 4;

	//インターバルを超えたらアニメーション
	int interval = 8;
	if (this->animCount >= interval) {
		this->animNum += 1;
		this->animCount = 0;
		if (this->animNum >= moveMotionNum) {
			this->animNum = 0; 
		}
	}

	//描画位置の設定を更新
	this->SetSrcPos(this->animNum * this->GetSizeDW(), this->motion * this->GetSizeDH());
}

void Player::HitMove(HitObjectBase& you) {
	//攻撃していない + ダメージを受けていない + 死んでいない
	if (motion == sword) return;
	if (motion == damage) return;
	if (motion == die) return;

	if (you.GetMyType() == Enemy) {
		//無敵の場合は処理を行わない
		if (GetIncincible_Time()) { return; }

		//体力減少
		hp -= 1;

		//ノックバック
		ResetNowSpeed();//速度リセット
		//向きの変更
		if (you.GetPosX() <= this->GetPosX()) {//自身より左にyouがいた場合
			this->angle = Angle::left;
		}
		else {//自身より右にyouがいた場合
			this->angle = Angle::right;
		}
		//モーション変更
		MotionChange(Motion::damage, true);
	}
}

void Player::PlayerGameClear() {
	if (motion == win) { return; }//ポーズが勝利なら処理は行わない
	if (motion == die) { return; }//ポーズが死亡なら処理は行わない
	if (Game::clearJudge()) {
		//モーション変更
		MotionChange(Motion::win, true);
		//BGMを止める
		int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
		StopSoundMem(*bgmAddress);
	}
}

void Player::CraeteAttackArea(hObj& hobj) {
	Game::AddList_AddBack(hobj);
}

void Player::DrawLifeGaugeUI() {

	//基準座標
	float dx = this->GetPosX() - ViewData::GetRenderPosX() - 25;
	float dy = this->GetPosY() - 50;

	//サイズ指定
	int sizeW = 913;
	int sizeH = 300;
	int srcX = 0;
	int srcY = 0;

	float magnification = 0.2f;

	//ゲージ背景ー＞ゲージー＞カバーの順で描画

	//ゲージ背景
	int* backImg = &Loader::PlayerGaugeBackImg;
	DrawRectExtendGraphF(dx, dy, dx + sizeW * magnification, dy + sizeH * magnification,
		srcX, srcY, sizeW, sizeH, *backImg, true);

	//ゲージ
	int* gaugeImg = &Loader::PlayerGaugeImg;
	int sizeLifeW = (sizeW / this->hpMax) * hp;
	//キャラを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF(dx, dy, dx + sizeLifeW * magnification, dy + sizeH * magnification,
		srcX, srcY, sizeLifeW, sizeH, *gaugeImg, true);


	//ゲージカバー
	int* coverImg = &Loader::PlayerGaugeCoverImg;
	//キャラを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF(dx, dy, dx + sizeW * magnification, dy + sizeH * magnification,
		srcX, srcY, sizeW, sizeH, *coverImg, true);

	//巻物の数を描画
	//指定マップの場合は白、ほかは黒
	int Color = GetColor(0, 0, 0);
	if (Map::mapNum == 2 || Map::mapNum == 3) {
		Color = GetColor(255, 255, 255);
	}
	SetFontSize(30);
	DrawFormatString(dx + 55, dy + 5, Color, "×%d", Game::clearItemCounter);
}
