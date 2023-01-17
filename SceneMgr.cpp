#include "DxLib.h"
#include "SceneMgr.h"

void ChengeScene(BaseScene* c_Scene) {
	SetBackgroundColor(0, 0, 0);  //背景を黒く
	SceneMgr_Finalize();    //シーンの終了処理
	delete m_Scene;         //旧シーンの開放
	m_Scene = c_Scene;      //次のシーンをセット
	SceneMgr_Initialize();  //シーンの初期化処理
}

//SceneMgrはSorceで使用
//初期化
void SceneMgr_Initialize() {
	m_Scene->Initialize();
}

//終了処理
void SceneMgr_Finalize() {
	m_Scene->Finalize();
}

//更新
void SceneMgr_Update() {
	m_Scene->Update();
}

//描画
void SceneMgr_Draw() {
	m_Scene->Draw();
}

