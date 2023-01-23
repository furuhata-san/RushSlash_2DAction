#include "DxLib.h"
#include <list>
#include <memory>
#include <algorithm>
#include "../tool/DataLoader.h"//BGMなどのデータ保存
#include "../tool/ViewData.h"//Veiwデータ
#include "../scene/SceneMgr.h"//シーンクラスヘッダー
#include "../scene/AddList.h"//リスト追加関数入りヘッダー
#include "../scene/GameMgr.h"//ゲームマネージャー
//以下オブジェクトクラスヘッダー
#include "../base/Object.h"
#include "../base/HitObjectBase.h"
#include "../map/Map.h"
#include "../object/Camera.h"

//シェアポインタ
//typedef std::shared_ptr<Object> Obj;
//typedef std::shared_ptr<HitObjectBase> hObj;

//通常のオブジェクトのリスト
//主にエフェクトなどのオブジェクトのリスト
std::list<Obj> objectList;

//当たり判定を持つオブジェクトのリスト
//主にプレイヤや敵、な攻撃範囲などのリスト
std::list<hObj> hitObjectList;

int Game::clearItemCounter = 0;

void GameScene::Initialize() {
    //マップをロード
    Map::LoadMapData(Map::mapNum);
    //BGMを鳴らす
    int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
    ChangeVolumeSoundMem(180, *bgmAddress);
    PlaySoundMem(*bgmAddress, DX_PLAYTYPE_LOOP);

    //カメラを生成
    Obj cameraObj = Obj(new Camera());
    Game::AddList_AddBack(cameraObj);
    //世界の中心
    ViewData::viewTarget = cameraObj;
}

void GameScene::Finalize() {
    //コンテナ内のものの解放処理を行う
    std::for_each(objectList.begin(), objectList.end(), [](Obj& o) {o->SetRemoveFlag(true); });
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [](hObj& o) {o->SetRemoveFlag(true); });
}

void GameScene::Update() {

    //収集目標アイテムのカウントを行う
    Game::itemCountReset();

    //オブジェクトごとの更新処理
    
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [](hObj& o) {
        
        o->update(); //更新処理

        if (ViewData::playerObject == o) {//プレイヤだった場合は座標更新（判定のサイズ）
            //プレイヤの中心座標
            ViewData::SetPlayerWorldPos(o->GetHitX() + (o->GetHitW() / 2), o->GetHitY() + (o->GetHitH() / 2));
        }

        if (o->GetMyType() == HitObjectBase::HitObjectType::Item) {//収集アイテムのカウント
            Game::itemCountUp();
        }

        });

    std::for_each(objectList.begin(), objectList.end(), [](Obj& o) {
        o->update();

        if (ViewData::viewTarget == o) {//ターゲットだった場合、描画座標を座標値に指定
            ViewData::SetRenderPos(o->GetPosX() - (ViewData::window_w / 2), o->GetPosY());

            //マップ配列外に移動しないよう位置を制限
            //X補正
            if (ViewData::GetRenderPosX() <= 0) ViewData::SetRenderPos(0, ViewData::GetRenderPosY());
            else if (ViewData::GetRenderPosX() >= Map::width * Map::blockSize - ViewData::window_w)
                ViewData::SetRenderPos(Map::width * Map::blockSize - ViewData::window_w, ViewData::GetRenderPosY());

            //Y補正
            if (ViewData::GetRenderPosY() <= 0) ViewData::SetRenderPos(ViewData::GetRenderPosX(), 0);
            else if (ViewData::GetRenderPosY() >= Map::height * Map::blockSize - ViewData::window_h)
                ViewData::SetRenderPos(ViewData::GetRenderPosX(), Map::height * Map::blockSize - ViewData::window_h);
        }

        });

    // 当たり判定
    //まず、全部のオブジェクトの中から、HitObjectBase継承を探す
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [&](hObj& me) {
        //総当たりを行う
        std::for_each(hitObjectList.begin(), hitObjectList.end(), [&](hObj& you) {
            //自分のヒットタイプと判定を行うタイプが一致した場合
            if (me->GetHitType() == you->GetMyType()) {
                //ヒットしているか判定
                if (me->HitJudge(*you)) {
                    //ヒットした場合は処理を行う
                    me->HitMove(*you);
                }
            }
            else if (me->GetHitType() == HitObjectBase::HitObjectType::AllHit) {//「me」が「AllHit」ならヒットしているかを判定
                //ヒットしているか判定
                if (me->HitJudge(*you)) {
                    //ヒットした場合は処理を行う
                    me->HitMove(*you);
                }
            }
        });
     });

    //消すべきオブジェクトの削除
    std::list<Obj>::iterator endO = std::remove_if(objectList.begin(), objectList.end(), [](Obj& o) {
        if (o->GetRemoveFlag()) {//フラグ参照
            o->finalize();
            return true;
        }
        return false;
        });
    objectList.erase(endO, objectList.end());//要素の削除（deleteではない）

    //上と同じ動作をHitObjectにも行う
    std::list<hObj>::iterator endHO = std::remove_if(hitObjectList.begin(), hitObjectList.end(), [](hObj& ho) {
        if (ho->GetRemoveFlag()) {//フラグ参照
            ho->finalize();
            return true;
        }
        return false;
        });
   
    hitObjectList.erase(endHO, hitObjectList.end());
}

void GameScene::Draw() {
    //マップの描画（マップはオブジェクトではない）
    Map::DrawMap();

    //オブジェクトごとの描画処理
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [](hObj& o) {o->draw(); });
    //エフェクトを後に描画する
    std::for_each(objectList.begin(), objectList.end(), [](Obj& o) {o->draw(); });
}


//AddList.h内の処理　当たり判定を持たないオブジェクトをリストに追加
void Game::AddList_AddFront(const Obj& obj) {
    objectList.push_front(obj);
}
void Game::AddList_AddBack(const Obj& obj) {
    objectList.push_back(obj);
}

//AddList.h内の処理　当たり判定を持つオブジェクトをリストに追加
void Game::AddList_AddFront(const hObj& hobj) {
    hitObjectList.push_front(hobj);
}
void Game::AddList_AddBack(const hObj& hobj) {
    hitObjectList.push_back(hobj);
}

void Game::itemCountUp() {
    Game::clearItemCounter++;
}
void Game::itemCountReset() {
    Game::clearItemCounter = 0;
}
bool Game::clearJudge() {
    return Game::clearItemCounter <= 0;
}