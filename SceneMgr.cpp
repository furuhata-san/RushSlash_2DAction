#include "DxLib.h"
#include "SceneMgr.h"

void ChengeScene(BaseScene* c_Scene) {
	SetBackgroundColor(0, 0, 0);  //�w�i������
	SceneMgr_Finalize();    //�V�[���̏I������
	delete m_Scene;         //���V�[���̊J��
	m_Scene = c_Scene;      //���̃V�[�����Z�b�g
	SceneMgr_Initialize();  //�V�[���̏���������
}

//SceneMgr��Sorce�Ŏg�p
//������
void SceneMgr_Initialize() {
	m_Scene->Initialize();
}

//�I������
void SceneMgr_Finalize() {
	m_Scene->Finalize();
}

//�X�V
void SceneMgr_Update() {
	m_Scene->Update();
}

//�`��
void SceneMgr_Draw() {
	m_Scene->Draw();
}

