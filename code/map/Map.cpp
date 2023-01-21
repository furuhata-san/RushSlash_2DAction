#define _CRT_SECURE_NO_WARNINGS

#include "Dxlib.h"
#include "../map/Map.h"
#include "../tool/DataLoader.h"
#include "../tool/ViewData.h"
#include "../scene/AddList.h"
#include "../tool/KeyChecker.h"
#include <string>
#include <vector>

//�}�b�v����ǉ��������I�u�W�F�N�g
#include "../player/Player.h"
#include "../enemy/Enemys.h"
#include "../object/GoalItem.h" 

namespace Map {

	const int width = 100;
	const int height = 15;
	int data[height][width];

	int* blockImage = &Loader::mapBlockImg;
	int mapNum = 0;

	int blockSize = 64;

	//�`�b�v��
	enum class chipName {
		air,
		block,
		enemyBlack,
		enemyRed,
		enemyBlue,
		enemyPurple,
		enemyGreen,
		itemRed,
		itemBlue,
		itemGreen,
		PlayerStart
	};
	extern std::string* GetChipName(chipName name);

	bool mapEditorFlag = false;

	void LoadMapData(int gn_) {

		//�ǂݍ��ނ��߂̃t�@�C�������쐬����
		char Filename[50];
		sprintf_s(Filename, sizeof(Filename), "./data/mapData/map%d.txt", gn_);//�Q�[���ԍ����g���ăt�@�C�������쐬
		int FileHandle = FileRead_open(Filename);	//�t�@�C�����J��

		//�t�@�C�����當�����ǂݎ��(+1��\n)
		char loadTextData[width * 3 + 1];

		//�z����̕���(����)�𐔒l�ɕϊ������
		for (int y = 0; y < height; ++y) {
			//�����ǂݍ���
			FileRead_gets(loadTextData, width * height + 1, FileHandle);

			//�ꕶ�����ǂݏグ�Ă���
			for (int x = 0, mapX = 0; mapX < width; ++x) {
				//�u���p�X�y�[�X�v���u�R���}�v�ȊO�̏ꍇ�͓ǂݍ���
				if (!((char)loadTextData[x] == ',' || (char)loadTextData[x] == ' ')) {
					int num = 0;
					hObj createObj;
					switch ((char)loadTextData[x]) {
						//�}�b�v�u���b�N
					case '0'://�Ȃ�
						num = 0;
						break;

					case '1'://��
						num = 1;
						break;


						//�G�l�~�[�n��
					case 'e':
						//���̔ԍ��ɂ���ēG��ύX����
						x++;
						switch ((char)loadTextData[x])
						{
						case 'K'://��
							createObj = hObj(new BlackEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'R'://��
							createObj = hObj(new RedEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'B'://��
							createObj = hObj(new BlueEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'G'://��
							createObj = hObj(new GreenEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'P'://��
							createObj = hObj(new PurpleEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						default://���̑�
							//nop
							break;
						}

						num = 0;//�}�b�v�ɂ͕ω��Ȃ�
						break;



						//�v���C��
					case 's':
						createObj = hObj(new Player(mapX * blockSize, y * blockSize));
						Game::AddList_AddBack(createObj);

						//�v���C�����̕ۑ�(�v���C���ɑ傫�Ȉُ킪���������ꍇ�͂������^��)
						ViewData::playerObject = createObj;

						num = 0;//�}�b�v�ɂ͕ω��Ȃ�
						break;



						//�S�[���A�C�e���i�����j
					case 'i':
						//���̔ԍ��ɂ���Ċ�����ύX����
						x++;
						switch ((char)loadTextData[x])
						{
						case 'R'://��
							createObj = hObj(new GoalItem(mapX * blockSize, y * blockSize, 0));
							Game::AddList_AddFront(createObj);
							break;

						case 'B'://��
							createObj = hObj(new GoalItem(mapX * blockSize, y * blockSize, 1));
							Game::AddList_AddFront(createObj);
							break;

						case 'G'://��
							createObj = hObj(new GoalItem(mapX * blockSize, y * blockSize, 2));
							Game::AddList_AddFront(createObj);
							break;

						default://���̑�
							//nop
							break;
						}

						num = 0;//�}�b�v�ɂ͕ω��Ȃ�
						break;


						//���̑��i�ʏ�͂��肦�Ȃ��j
					default: //��L��case�ȊO�̏ꍇ

						num = 1;//�u���b�N���i�G���[����Ŏ����j

						break;
					}

					//�}�b�v�ɔԍ��o�^�����̗v�f��
					data[y][mapX] = num;
					mapX++;
				}
			}
		}

		//���[�v�I��
		FileRead_close(FileHandle);//�t�@�C�������
	}

	int GetMapChip(int y, int x) {

		return data[y][x];

	}

	void DrawMap() {

		//�܂��w�i�`��
		int* backImage = &Loader::backImg[mapNum];
		//��ʃT�C�Y�ɍ��킹��
		DrawRectExtendGraphF(0, 0, ViewData::size_w, ViewData::size_h, 0, 0, 640, 480, *backImage, true);

		//�X�N���[���̒��ɕ`��ł���ʂ������[�v
		for (int y = 0; y <= ViewData::size_h / blockSize; ++y) {
			for (int x = 0; x <= ViewData::size_w / blockSize; ++x) {
				//�}�b�v�`�b�v�������W�X�N���[���Ή�
				float bx_ = (float)(x + (int)(ViewData::GetRenderPosX() / blockSize));
				float by_ = (float)y;

				if (GetMapChip((int)by_, (int)bx_) == 1) {//�`�b�v����
					//�`��X���W���X�N���[���Ή������Ă���}�b�v�`��
					//�ux * 64�v����@0�`64�̒l�������ĕ`��<-�^�[�Q�b�g�̍��W�̏�] 
					float blockDrawPosX = (x * blockSize) - ((int)ViewData::GetRenderPosX() % blockSize);
					//��ʓ��̏ꍇ�͕`��
					if (-blockSize <= blockDrawPosX && blockDrawPosX <= ViewData::size_w + blockSize)
						DrawGraphF(blockDrawPosX, (float)y * blockSize, *blockImage, false);
				}
			}
		}
	}

	//�}�b�v�S�̂̂����̃{�b�N�X�͈͂����[�v
	bool MapCheckHit(float hitboxX, float hitboxY, float hitboxW, float hitboxH) {

		//�󂯎�����I�u�W�F�N�g��
		//�����蔻��̎l�����}�X�ڂɕϊ����A
		//�u���b�N�ł���Ɗm�F���ꂽ��true��Ԃ�

		//�}�X�ڂɕϊ�
		int castXL = (hitboxX) / blockSize;
		int castXR = ((hitboxX + hitboxW)) / blockSize;
		int castYL = (hitboxY) / blockSize;
		int castYR = ((hitboxY + hitboxH)) / blockSize;

		//�쐬�����}�X�ڂƏd�Ȃ��Ă��镔���ƃ}�X�ڂ̓������ǂȂ�true
		for (int y = castYL; y <= castYR; ++y) {
			for (int x = castXL; x <= castXR; ++x) {
				//�z��O���Q�Ƃ��Ȃ��悤�ɂ���
				if (x >= 0) {
					if (x < width) {
						if (y >= 0) {
							if (y < height) {
								//���W�ɕϊ������}�X�ڂ��ǂ������ꍇ��true
								if (data[y][x] == 1) return true;
							}
						}
					}
				}

			}
		}
		return false;
	}
}

