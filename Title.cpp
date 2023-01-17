#include "DxLib.h"
#include "DataLoader.h"
#include "ViewData.h"//Veiwデータ
#include "KeyChecker.h"
#include "SceneMgr.h"//シーンクラスヘッダー
#include "Map.h"
/*
タイトル画面の描画や処理は
このソースコードだけで済ませること

オブジェクトとして作成するのはゲームシーンのみとする
*/
namespace Title {
	int* backImage;//背景
	void BackDraw(float x, float y);

	int* logoImage;//タイトルロゴ
	void LogoDraw(float x, float y);

	int* charaImage;//キャラ
	float charaAnimCnt;//キャラクターのアニメーション用カウント
	void CharaDraw(float x, float y, float magnification);

	//ステージセレクト文字
	int* selectTextImage;
	float selectTextGifCount;
	void SelectTextDraw(float x, float y);

	int* flameImage;//セレクトフレーム
	void FlameDraw();

	//複製しやすくするため、ボタンをクラス化する。
	class StageButton {
		int* iconImage;
		int* textImage;
		float x, y, w, h;
	public:
		//情報セット
		void SetImageAddress(int* iconAddress, int* textAddress) { iconImage = iconAddress; textImage = textAddress; }
		void SetPos(float x_, float y_) { x = x_; y = y_; }
		void SetSize(float w_, float h_) { w = w_; h = h_; }

		//フレームの位置調整用
		float GetPosX() { return this->x; }
		float GetPosY() { return this->y; }
		float GetSizeW() { return this->w; }
		float GetSizeH() { return this->h; }

		//描画
		void Draw(int i) {
			//サイズに合わせてアイコンー＞テキストの順で描画
			DrawRectExtendGraphF(x, y, x + w, y + h,
				0, 0, 640, 480, *iconImage, false);
			DrawRectExtendGraphF(x, y, x + w, y + h,
				0, 0, 250, 150, *textImage, true);
		}
	};
	const int stageNum = 4;//ステージ数
	StageButton stageButton[stageNum];
	int nowSelectStageNum; //今選んでいるステージ番号
	int selectPageDown = 2;//セレクト画面で横に並べるステージ数

	void SelectMap();
}

void TitleScene::Initialize() {
	//画像のアドレスを取得
	Title::backImage = &Loader::titleBackImg;
	Title::logoImage = &Loader::titleTextImg;
	Title::charaImage = &Loader::playerImg;
	Title::flameImage = &Loader::titleSelectFlame;
	Title::selectTextImage = &Loader::stageSelectTexts;

	//値の初期化
	Title::charaAnimCnt = 0;
	Title::nowSelectStageNum = Map::mapNum;
	Title::selectTextGifCount = 0;

	for (int i = 0; i < Title::stageNum; ++i) {
		//画像アドレス値セット
		Title::stageButton[i].
			SetImageAddress(&Loader::backImg[i], &Loader::titleStageTextImg[i]);
		//座標等の情報入力
		float drawPosX = 150.0f + 300.0f * (i % Title::selectPageDown) + (100.0f * (i / 2));
		float drawPosY = 450.0f + 200.0f * (i / Title::selectPageDown);
		Title::stageButton[i].SetPos(drawPosX, drawPosY);
		Title::stageButton[i].SetSize(250, 150);
	}

	//BGMを鳴らす
	int* bgmAddress = &Loader::TitleBGM;
	ChangeVolumeSoundMem(255 / 2, *bgmAddress);
	PlaySoundMem(*bgmAddress, DX_PLAYTYPE_LOOP);
}

void TitleScene::Finalize() {
	//BGMを止める
	int* bgmAddress = &Loader::TitleBGM;
	StopSoundMem(*bgmAddress);
}

void TitleScene::Update() {
	Title::SelectMap();
}

void TitleScene::Draw() {

	//下に描画したいもの順
	Title::BackDraw(0,0);
	Title::LogoDraw(300,100);
	Title::CharaDraw(800,350,3.5f);

	DrawBox(100, 325, 100 + 250 * 3, 370 + 150 * 3, 0, true);//黒背景
	Title::SelectTextDraw(100 + (250 / 2), 325);//文字
	for (int i = 0; i < Title::stageNum; ++i) {	//アイコンを並べて表示
		Title::stageButton[i].Draw(i);
	}
	//選択中のステージ
	Title::FlameDraw();


}

void Title::BackDraw(float x, float y) {
	int srcX = 0;
	int srcY = 0;
	int srcW = 1280;
	int srcH = 960;
	int sizeW = ViewData::size_w;
	int sizeH = ViewData::size_h;

	//背景描画
	DrawRectExtendGraphF(x, y, x + sizeW, y + sizeH,
		srcX, srcY, srcW, srcH, *backImage, false);

}

void Title::LogoDraw(float x, float y) {
	//位置・サイズ指定
	int srcX = 0;
	int srcY = 0;
	int srcW = 558;
	int srcH = 152;
	float sizeW = srcW * 1.2f;
	float sizeH = srcH * 1.2f;

	//背景描画
	DrawRectExtendGraphF(x, y, x + sizeW, y + sizeH,
		srcX, srcY, srcW, srcH, *logoImage, true);
}

void Title::CharaDraw(float x, float y, float magnification) {
	
	//カウント増加
	charaAnimCnt += 0.1f;

	//サイズ指定
	int sizeW = 140;
	int sizeH = 140;
	int srcX = sizeW * ((int)charaAnimCnt % 4);
	int srcY = sizeH * 3;

	//キャラを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF(x, y, x + sizeW * magnification, y + sizeH * magnification,
		srcX, srcY, sizeW, sizeH,	*charaImage, true);
}

void Title::SelectTextDraw(float x, float y) {

	selectTextGifCount += 0.1f;//カウント増加

	//サイズ指定
	int sizeW = 467;
	int sizeH = 113;
	int srcX = 0;
	int srcY = sizeH * ((int)selectTextGifCount % 7);

	//キャラを描画（この式を行うことで読み込む画像が一枚で済む）
	DrawRectExtendGraphF(x, y, x + sizeW, y + sizeH,
		srcX, srcY, sizeW, sizeH, *selectTextImage, false);

}

void Title::FlameDraw() {
	float srcX = 0;
	float srcY = 0;
	float srcW = 275;
	float srcH = 175;
	//最初のボタンを代表として、ボタンのサイズを得て位置調整
	float posX = stageButton[nowSelectStageNum].GetPosX() - (25 / 2.0f);
	float posY = stageButton[nowSelectStageNum].GetPosY() - (25 / 2.0f);
	float sizeW = srcW;
	float sizeH = srcH;

	//フレーム描画
	DrawRectExtendGraphF(posX, posY, posX + sizeW, posY + sizeH,
		(int)srcX, (int)srcY, (int)srcW, (int)srcH, *flameImage, true);
}

void Title::SelectMap(){
	//上下左右の入力に応じて、選択しているステージを変更
	if (KeyChecker::InputDown(KEY_INPUT_LEFT) || KeyChecker::InputDown(KEY_INPUT_A)) {
		nowSelectStageNum -= 1;
		//配列外を参照時、補正（ステージ最後尾へ）
		if (nowSelectStageNum < 0) {
			nowSelectStageNum = stageNum - 1;
		}
	}
	else if (KeyChecker::InputDown(KEY_INPUT_RIGHT) || KeyChecker::InputDown(KEY_INPUT_D)) {
		nowSelectStageNum += 1;
		//配列外を参照時、補正（ステージ最前列へ）
		if (Title::nowSelectStageNum >= stageNum) {
			nowSelectStageNum = 0;
		}
	}
	else if (KeyChecker::InputDown(KEY_INPUT_UP) || KeyChecker::InputDown(KEY_INPUT_W)) {
		nowSelectStageNum -= selectPageDown;
		//配列外を参照時、補正（下の段へ）
		if (nowSelectStageNum < 0) {
			nowSelectStageNum += selectPageDown * 2;//元の値へ戻す＋次の段へ移動
		}
	}
	else if (KeyChecker::InputDown(KEY_INPUT_DOWN) || KeyChecker::InputDown(KEY_INPUT_S)) {
		nowSelectStageNum += selectPageDown;
		//配列外を参照時、補正（下の段へ）
		if (nowSelectStageNum >= stageNum) {
			nowSelectStageNum -= selectPageDown * 2;//元の値へ戻す＋次の段へ移動
		}
	}

	if (KeyChecker::InputUp(KEY_INPUT_RETURN) || KeyChecker::InputUp(KEY_INPUT_SPACE)) {
		//読み込むマップ番号を先に変更してからシーン変更
		Map::mapNum = nowSelectStageNum;
		ChengeScene(new GameScene);
	}
}