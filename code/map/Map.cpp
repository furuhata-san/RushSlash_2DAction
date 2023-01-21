#define _CRT_SECURE_NO_WARNINGS

#include "Dxlib.h"
#include "../map/Map.h"
#include "../tool/DataLoader.h"
#include "../tool/ViewData.h"
#include "../scene/AddList.h"
#include "../tool/KeyChecker.h"
#include <string>
#include <vector>

//マップから追加したいオブジェクト
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

	//チップ名
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

		//読み込むためのファイル名を作成する
		char Filename[50];
		sprintf_s(Filename, sizeof(Filename), "./data/mapData/map%d.txt", gn_);//ゲーム番号を使ってファイル名を作成
		int FileHandle = FileRead_open(Filename);	//ファイルを開く

		//ファイルから文字列を読み取り(+1は\n)
		char loadTextData[width * 3 + 1];

		//配列内の文字(数字)を数値に変換し代入
		for (int y = 0; y < height; ++y) {
			//横一列読み込む
			FileRead_gets(loadTextData, width * height + 1, FileHandle);

			//一文字ずつ読み上げていく
			for (int x = 0, mapX = 0; mapX < width; ++x) {
				//「半角スペース」か「コンマ」以外の場合は読み込む
				if (!((char)loadTextData[x] == ',' || (char)loadTextData[x] == ' ')) {
					int num = 0;
					hObj createObj;
					switch ((char)loadTextData[x]) {
						//マップブロック
					case '0'://なし
						num = 0;
						break;

					case '1'://壁
						num = 1;
						break;


						//エネミー系統
					case 'e':
						//次の番号によって敵を変更する
						x++;
						switch ((char)loadTextData[x])
						{
						case 'K'://黒
							createObj = hObj(new BlackEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'R'://赤
							createObj = hObj(new RedEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'B'://青
							createObj = hObj(new BlueEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'G'://緑
							createObj = hObj(new GreenEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						case 'P'://紫
							createObj = hObj(new PurpleEnemy(mapX * blockSize, y * blockSize));
							Game::AddList_AddBack(createObj);
							break;

						default://その他
							//nop
							break;
						}

						num = 0;//マップには変化なし
						break;



						//プレイヤ
					case 's':
						createObj = hObj(new Player(mapX * blockSize, y * blockSize));
						Game::AddList_AddBack(createObj);

						//プレイヤ情報の保存(プレイヤに大きな異常が発生した場合はここを疑う)
						ViewData::playerObject = createObj;

						num = 0;//マップには変化なし
						break;



						//ゴールアイテム（巻物）
					case 'i':
						//次の番号によって巻物を変更する
						x++;
						switch ((char)loadTextData[x])
						{
						case 'R'://赤
							createObj = hObj(new GoalItem(mapX * blockSize, y * blockSize, 0));
							Game::AddList_AddFront(createObj);
							break;

						case 'B'://青
							createObj = hObj(new GoalItem(mapX * blockSize, y * blockSize, 1));
							Game::AddList_AddFront(createObj);
							break;

						case 'G'://緑
							createObj = hObj(new GoalItem(mapX * blockSize, y * blockSize, 2));
							Game::AddList_AddFront(createObj);
							break;

						default://その他
							//nop
							break;
						}

						num = 0;//マップには変化なし
						break;


						//その他（通常はありえない）
					default: //上記のcase以外の場合

						num = 1;//ブロック化（エラーを後で実装）

						break;
					}

					//マップに番号登録し次の要素へ
					data[y][mapX] = num;
					mapX++;
				}
			}
		}

		//ループ終了
		FileRead_close(FileHandle);//ファイルを閉じる
	}

	int GetMapChip(int y, int x) {

		return data[y][x];

	}

	void DrawMap() {

		//まず背景描画
		int* backImage = &Loader::backImg[mapNum];
		//画面サイズに合わせる
		DrawRectExtendGraphF(0, 0, ViewData::size_w, ViewData::size_h, 0, 0, 640, 480, *backImage, true);

		//スクリーンの中に描画できる量だけループ
		for (int y = 0; y <= ViewData::size_h / blockSize; ++y) {
			for (int x = 0; x <= ViewData::size_w / blockSize; ++x) {
				//マップチップ検索座標スクロール対応
				float bx_ = (float)(x + (int)(ViewData::GetRenderPosX() / blockSize));
				float by_ = (float)y;

				if (GetMapChip((int)by_, (int)bx_) == 1) {//チップ検索
					//描画X座標をスクロール対応させてからマップ描画
					//「x * 64」から　0～64の値を引いて描画<-ターゲットの座標の剰余 
					float blockDrawPosX = (x * blockSize) - ((int)ViewData::GetRenderPosX() % blockSize);
					//画面内の場合は描画
					if (-blockSize <= blockDrawPosX && blockDrawPosX <= ViewData::size_w + blockSize)
						DrawGraphF(blockDrawPosX, (float)y * blockSize, *blockImage, false);
				}
			}
		}
	}

	//マップ全体のうちのボックス範囲をループ
	bool MapCheckHit(float hitboxX, float hitboxY, float hitboxW, float hitboxH) {

		//受け取ったオブジェクトの
		//当たり判定の四隅をマス目に変換し、
		//ブロックであると確認されたらtrueを返す

		//マス目に変換
		int castXL = (hitboxX) / blockSize;
		int castXR = ((hitboxX + hitboxW)) / blockSize;
		int castYL = (hitboxY) / blockSize;
		int castYR = ((hitboxY + hitboxH)) / blockSize;

		//作成したマス目と重なっている部分とマス目の内側が壁ならtrue
		for (int y = castYL; y <= castYR; ++y) {
			for (int x = castXL; x <= castXR; ++x) {
				//配列外を参照しないようにする
				if (x >= 0) {
					if (x < width) {
						if (y >= 0) {
							if (y < height) {
								//座標に変換したマス目が壁だった場合はtrue
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

