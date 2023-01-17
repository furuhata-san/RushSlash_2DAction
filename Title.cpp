#include "DxLib.h"
#include "DataLoader.h"
#include "ViewData.h"//Veiw�f�[�^
#include "KeyChecker.h"
#include "SceneMgr.h"//�V�[���N���X�w�b�_�[
#include "Map.h"
/*
�^�C�g����ʂ̕`��⏈����
���̃\�[�X�R�[�h�����ōς܂��邱��

�I�u�W�F�N�g�Ƃ��č쐬����̂̓Q�[���V�[���݂̂Ƃ���
*/
namespace Title {
	int* backImage;//�w�i
	void BackDraw(float x, float y);

	int* logoImage;//�^�C�g�����S
	void LogoDraw(float x, float y);

	int* charaImage;//�L����
	float charaAnimCnt;//�L�����N�^�[�̃A�j���[�V�����p�J�E���g
	void CharaDraw(float x, float y, float magnification);

	//�X�e�[�W�Z���N�g����
	int* selectTextImage;
	float selectTextGifCount;
	void SelectTextDraw(float x, float y);

	int* flameImage;//�Z���N�g�t���[��
	void FlameDraw();

	//�������₷�����邽�߁A�{�^�����N���X������B
	class StageButton {
		int* iconImage;
		int* textImage;
		float x, y, w, h;
	public:
		//���Z�b�g
		void SetImageAddress(int* iconAddress, int* textAddress) { iconImage = iconAddress; textImage = textAddress; }
		void SetPos(float x_, float y_) { x = x_; y = y_; }
		void SetSize(float w_, float h_) { w = w_; h = h_; }

		//�t���[���̈ʒu�����p
		float GetPosX() { return this->x; }
		float GetPosY() { return this->y; }
		float GetSizeW() { return this->w; }
		float GetSizeH() { return this->h; }

		//�`��
		void Draw(int i) {
			//�T�C�Y�ɍ��킹�ăA�C�R���[���e�L�X�g�̏��ŕ`��
			DrawRectExtendGraphF(x, y, x + w, y + h,
				0, 0, 640, 480, *iconImage, false);
			DrawRectExtendGraphF(x, y, x + w, y + h,
				0, 0, 250, 150, *textImage, true);
		}
	};
	const int stageNum = 4;//�X�e�[�W��
	StageButton stageButton[stageNum];
	int nowSelectStageNum; //���I��ł���X�e�[�W�ԍ�
	int selectPageDown = 2;//�Z���N�g��ʂŉ��ɕ��ׂ�X�e�[�W��

	void SelectMap();
}

void TitleScene::Initialize() {
	//�摜�̃A�h���X���擾
	Title::backImage = &Loader::titleBackImg;
	Title::logoImage = &Loader::titleTextImg;
	Title::charaImage = &Loader::playerImg;
	Title::flameImage = &Loader::titleSelectFlame;
	Title::selectTextImage = &Loader::stageSelectTexts;

	//�l�̏�����
	Title::charaAnimCnt = 0;
	Title::nowSelectStageNum = Map::mapNum;
	Title::selectTextGifCount = 0;

	for (int i = 0; i < Title::stageNum; ++i) {
		//�摜�A�h���X�l�Z�b�g
		Title::stageButton[i].
			SetImageAddress(&Loader::backImg[i], &Loader::titleStageTextImg[i]);
		//���W���̏�����
		float drawPosX = 150.0f + 300.0f * (i % Title::selectPageDown) + (100.0f * (i / 2));
		float drawPosY = 450.0f + 200.0f * (i / Title::selectPageDown);
		Title::stageButton[i].SetPos(drawPosX, drawPosY);
		Title::stageButton[i].SetSize(250, 150);
	}

	//BGM��炷
	int* bgmAddress = &Loader::TitleBGM;
	ChangeVolumeSoundMem(255 / 2, *bgmAddress);
	PlaySoundMem(*bgmAddress, DX_PLAYTYPE_LOOP);
}

void TitleScene::Finalize() {
	//BGM���~�߂�
	int* bgmAddress = &Loader::TitleBGM;
	StopSoundMem(*bgmAddress);
}

void TitleScene::Update() {
	Title::SelectMap();
}

void TitleScene::Draw() {

	//���ɕ`�悵�������̏�
	Title::BackDraw(0,0);
	Title::LogoDraw(300,100);
	Title::CharaDraw(800,350,3.5f);

	DrawBox(100, 325, 100 + 250 * 3, 370 + 150 * 3, 0, true);//���w�i
	Title::SelectTextDraw(100 + (250 / 2), 325);//����
	for (int i = 0; i < Title::stageNum; ++i) {	//�A�C�R������ׂĕ\��
		Title::stageButton[i].Draw(i);
	}
	//�I�𒆂̃X�e�[�W
	Title::FlameDraw();


}

void Title::BackDraw(float x, float y) {
	int srcX = 0;
	int srcY = 0;
	int srcW = 1280;
	int srcH = 960;
	int sizeW = ViewData::size_w;
	int sizeH = ViewData::size_h;

	//�w�i�`��
	DrawRectExtendGraphF(x, y, x + sizeW, y + sizeH,
		srcX, srcY, srcW, srcH, *backImage, false);

}

void Title::LogoDraw(float x, float y) {
	//�ʒu�E�T�C�Y�w��
	int srcX = 0;
	int srcY = 0;
	int srcW = 558;
	int srcH = 152;
	float sizeW = srcW * 1.2f;
	float sizeH = srcH * 1.2f;

	//�w�i�`��
	DrawRectExtendGraphF(x, y, x + sizeW, y + sizeH,
		srcX, srcY, srcW, srcH, *logoImage, true);
}

void Title::CharaDraw(float x, float y, float magnification) {
	
	//�J�E���g����
	charaAnimCnt += 0.1f;

	//�T�C�Y�w��
	int sizeW = 140;
	int sizeH = 140;
	int srcX = sizeW * ((int)charaAnimCnt % 4);
	int srcY = sizeH * 3;

	//�L������`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF(x, y, x + sizeW * magnification, y + sizeH * magnification,
		srcX, srcY, sizeW, sizeH,	*charaImage, true);
}

void Title::SelectTextDraw(float x, float y) {

	selectTextGifCount += 0.1f;//�J�E���g����

	//�T�C�Y�w��
	int sizeW = 467;
	int sizeH = 113;
	int srcX = 0;
	int srcY = sizeH * ((int)selectTextGifCount % 7);

	//�L������`��i���̎����s�����Ƃœǂݍ��މ摜���ꖇ�ōςށj
	DrawRectExtendGraphF(x, y, x + sizeW, y + sizeH,
		srcX, srcY, sizeW, sizeH, *selectTextImage, false);

}

void Title::FlameDraw() {
	float srcX = 0;
	float srcY = 0;
	float srcW = 275;
	float srcH = 175;
	//�ŏ��̃{�^�����\�Ƃ��āA�{�^���̃T�C�Y�𓾂Ĉʒu����
	float posX = stageButton[nowSelectStageNum].GetPosX() - (25 / 2.0f);
	float posY = stageButton[nowSelectStageNum].GetPosY() - (25 / 2.0f);
	float sizeW = srcW;
	float sizeH = srcH;

	//�t���[���`��
	DrawRectExtendGraphF(posX, posY, posX + sizeW, posY + sizeH,
		(int)srcX, (int)srcY, (int)srcW, (int)srcH, *flameImage, true);
}

void Title::SelectMap(){
	//�㉺���E�̓��͂ɉ����āA�I�����Ă���X�e�[�W��ύX
	if (KeyChecker::InputDown(KEY_INPUT_LEFT) || KeyChecker::InputDown(KEY_INPUT_A)) {
		nowSelectStageNum -= 1;
		//�z��O���Q�Ǝ��A�␳�i�X�e�[�W�Ō���ցj
		if (nowSelectStageNum < 0) {
			nowSelectStageNum = stageNum - 1;
		}
	}
	else if (KeyChecker::InputDown(KEY_INPUT_RIGHT) || KeyChecker::InputDown(KEY_INPUT_D)) {
		nowSelectStageNum += 1;
		//�z��O���Q�Ǝ��A�␳�i�X�e�[�W�őO��ցj
		if (Title::nowSelectStageNum >= stageNum) {
			nowSelectStageNum = 0;
		}
	}
	else if (KeyChecker::InputDown(KEY_INPUT_UP) || KeyChecker::InputDown(KEY_INPUT_W)) {
		nowSelectStageNum -= selectPageDown;
		//�z��O���Q�Ǝ��A�␳�i���̒i�ցj
		if (nowSelectStageNum < 0) {
			nowSelectStageNum += selectPageDown * 2;//���̒l�֖߂��{���̒i�ֈړ�
		}
	}
	else if (KeyChecker::InputDown(KEY_INPUT_DOWN) || KeyChecker::InputDown(KEY_INPUT_S)) {
		nowSelectStageNum += selectPageDown;
		//�z��O���Q�Ǝ��A�␳�i���̒i�ցj
		if (nowSelectStageNum >= stageNum) {
			nowSelectStageNum -= selectPageDown * 2;//���̒l�֖߂��{���̒i�ֈړ�
		}
	}

	if (KeyChecker::InputUp(KEY_INPUT_RETURN) || KeyChecker::InputUp(KEY_INPUT_SPACE)) {
		//�ǂݍ��ރ}�b�v�ԍ����ɕύX���Ă���V�[���ύX
		Map::mapNum = nowSelectStageNum;
		ChengeScene(new GameScene);
	}
}