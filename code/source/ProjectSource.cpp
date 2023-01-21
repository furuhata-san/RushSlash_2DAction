#include "DxLib.h"

#include "../tool/ViewData.h"
#include "../tool/KeyChecker.h"

#include "../scene/SceneMgr.h"
#include "../tool/DataLoader.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//前準備
	SetOutApplicationLogValidFlag(FALSE);	//log.txtを出力しません

	//ウィンドウのサイズを指定、リフレッシュレート仮処理
	int WindowChange = SetGraphMode(ViewData::size_w, ViewData::size_h, 32, 60);
	if (WindowChange == DX_CHANGESCREEN_REFRESHNORMAL) {
		return -1;
	}

	SetMainWindowText("Rush Slash");	//名前変更
	ChangeWindowMode(TRUE);			//ウィンドウモード
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);  //ウィンドウモード変更と初期化と裏画面設定
	
	Loader::ImageLoadWave0();
	
	//ロード中の文字だけを描画
	int nowLoadingTextImg = LoadGraph("./data/textImage/NowLoading.png");
	int loadTextPosX = ViewData::size_w - 487;
	int loadTextPosY = ViewData::size_h - 106;
	DrawGraph(loadTextPosX, loadTextPosY, nowLoadingTextImg, true);
	ScreenFlip();//画面反転

	Loader::ImageLoadWave1();
	Loader::ImageLoadWave2();
	Loader::ImageLoadWave3();
	Loader::ImageLoadWave4();

	Loader::BGMLoad();
	Loader::SELoad();

	//シーンの初期化
	SceneMgr_Initialize();

	//ロード完了後、ロード中の文字画像を解放
	DeleteGraph(nowLoadingTextImg);


	//画面更新・メッセージ処理・画面消去　これらをループさせる
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		
		//常にループさせておくべきものを以下に記述
		KeyChecker::GetHitKeyState_UpDate();

		SetWaitVSyncFlag(FALSE);

		SceneMgr_Update();
		SceneMgr_Draw();

		//Escapeキーが押された場合、ループを抜ける
		if (KeyChecker::InputUp(KEY_INPUT_ESCAPE)) {
			break;
		}
	}

	SceneMgr_Finalize();
	
	//読み込んだ情報を開放
	Loader::AllImageDelete();
	Loader::AllBGMDelete();
	Loader::AllSEDelete();

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}