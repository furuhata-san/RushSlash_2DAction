#pragma once

//シーンを変更するだけの関数（ProjectSource.cppで使用）
extern void SceneMgr_Initialize();//初期化
extern void SceneMgr_Finalize();//終了処理
extern void SceneMgr_Update();//更新
extern void SceneMgr_Draw();//描画

//以下シーンごとのクラス
//ベースとなるシーンクラス
struct BaseScene {
	virtual void Initialize() {};
	virtual void Finalize() {};
	virtual void Update() {};
	virtual void Draw() {};
};

//以下、上記BaseSceneを継承させてシーンを宣言

struct TitleScene : public BaseScene {
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};

struct GameScene : public BaseScene {
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};

//struct EndingScene : public BaseScene {
//	void Initialize() override;
//	void Finalize() override;
//	void Update() override;
//	void Draw() override;
//};

//シ－ン変更の関数	(この関数を一番下にしないと構文エラーが発生します)
static BaseScene* m_Scene = new TitleScene();//最初に表示したいシーンを挿入
extern void ChengeScene(BaseScene* c_Scene);