#include "DxLib.h"

#include "../tool/ViewData.h"
#include "../tool/KeyChecker.h"

#include "../scene/SceneMgr.h"
#include "../tool/DataLoader.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//�O����
	SetOutApplicationLogValidFlag(FALSE);	//log.txt���o�͂��܂���

	//�E�B���h�E�̃T�C�Y���w��A���t���b�V�����[�g������
	int WindowChange = SetGraphMode(ViewData::size_w, ViewData::size_h, 32, 60);
	if (WindowChange == DX_CHANGESCREEN_REFRESHNORMAL) {
		return -1;
	}

	SetMainWindowText("Rush Slash");	//���O�ύX
	ChangeWindowMode(TRUE);			//�E�B���h�E���[�h
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);  //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	
	Loader::ImageLoadWave0();
	
	//���[�h���̕���������`��
	int nowLoadingTextImg = LoadGraph("./data/textImage/NowLoading.png");
	int loadTextPosX = ViewData::size_w - 487;
	int loadTextPosY = ViewData::size_h - 106;
	DrawGraph(loadTextPosX, loadTextPosY, nowLoadingTextImg, true);
	ScreenFlip();//��ʔ��]

	Loader::ImageLoadWave1();
	Loader::ImageLoadWave2();
	Loader::ImageLoadWave3();
	Loader::ImageLoadWave4();

	Loader::BGMLoad();
	Loader::SELoad();

	//�V�[���̏�����
	SceneMgr_Initialize();

	//���[�h������A���[�h���̕����摜�����
	DeleteGraph(nowLoadingTextImg);


	//��ʍX�V�E���b�Z�[�W�����E��ʏ����@���������[�v������
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		
		//��Ƀ��[�v�����Ă����ׂ����̂��ȉ��ɋL�q
		KeyChecker::GetHitKeyState_UpDate();

		SetWaitVSyncFlag(FALSE);

		SceneMgr_Update();
		SceneMgr_Draw();

		//Escape�L�[�������ꂽ�ꍇ�A���[�v�𔲂���
		if (KeyChecker::InputUp(KEY_INPUT_ESCAPE)) {
			break;
		}
	}

	SceneMgr_Finalize();
	
	//�ǂݍ��񂾏����J��
	Loader::AllImageDelete();
	Loader::AllBGMDelete();
	Loader::AllSEDelete();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}