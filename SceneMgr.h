#pragma once

//�V�[����ύX���邾���̊֐��iProjectSource.cpp�Ŏg�p�j
extern void SceneMgr_Initialize();//������
extern void SceneMgr_Finalize();//�I������
extern void SceneMgr_Update();//�X�V
extern void SceneMgr_Draw();//�`��

//�ȉ��V�[�����Ƃ̃N���X
//�x�[�X�ƂȂ�V�[���N���X
struct BaseScene {
	virtual void Initialize() {};
	virtual void Finalize() {};
	virtual void Update() {};
	virtual void Draw() {};
};

//�ȉ��A��LBaseScene���p�������ăV�[����錾

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

//�V�|���ύX�̊֐�	(���̊֐�����ԉ��ɂ��Ȃ��ƍ\���G���[���������܂�)
static BaseScene* m_Scene = new TitleScene();//�ŏ��ɕ\���������V�[����}��
extern void ChengeScene(BaseScene* c_Scene);