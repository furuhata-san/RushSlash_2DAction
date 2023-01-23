#include "DxLib.h"
#include <list>
#include <memory>
#include <algorithm>
#include "../tool/DataLoader.h"//BGM�Ȃǂ̃f�[�^�ۑ�
#include "../tool/ViewData.h"//Veiw�f�[�^
#include "../scene/SceneMgr.h"//�V�[���N���X�w�b�_�[
#include "../scene/AddList.h"//���X�g�ǉ��֐�����w�b�_�[
#include "../scene/GameMgr.h"//�Q�[���}�l�[�W���[
//�ȉ��I�u�W�F�N�g�N���X�w�b�_�[
#include "../base/Object.h"
#include "../base/HitObjectBase.h"
#include "../map/Map.h"
#include "../object/Camera.h"

//�V�F�A�|�C���^
//typedef std::shared_ptr<Object> Obj;
//typedef std::shared_ptr<HitObjectBase> hObj;

//�ʏ�̃I�u�W�F�N�g�̃��X�g
//��ɃG�t�F�N�g�Ȃǂ̃I�u�W�F�N�g�̃��X�g
std::list<Obj> objectList;

//�����蔻������I�u�W�F�N�g�̃��X�g
//��Ƀv���C����G�A�ȍU���͈͂Ȃǂ̃��X�g
std::list<hObj> hitObjectList;

int Game::clearItemCounter = 0;

void GameScene::Initialize() {
    //�}�b�v�����[�h
    Map::LoadMapData(Map::mapNum);
    //BGM��炷
    int* bgmAddress = &Loader::GameBGMTrack[Map::mapNum];
    ChangeVolumeSoundMem(180, *bgmAddress);
    PlaySoundMem(*bgmAddress, DX_PLAYTYPE_LOOP);

    //�J�����𐶐�
    Obj cameraObj = Obj(new Camera());
    Game::AddList_AddBack(cameraObj);
    //���E�̒��S
    ViewData::viewTarget = cameraObj;
}

void GameScene::Finalize() {
    //�R���e�i���̂��̂̉���������s��
    std::for_each(objectList.begin(), objectList.end(), [](Obj& o) {o->SetRemoveFlag(true); });
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [](hObj& o) {o->SetRemoveFlag(true); });
}

void GameScene::Update() {

    //���W�ڕW�A�C�e���̃J�E���g���s��
    Game::itemCountReset();

    //�I�u�W�F�N�g���Ƃ̍X�V����
    
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [](hObj& o) {
        
        o->update(); //�X�V����

        if (ViewData::playerObject == o) {//�v���C���������ꍇ�͍��W�X�V�i����̃T�C�Y�j
            //�v���C���̒��S���W
            ViewData::SetPlayerWorldPos(o->GetHitX() + (o->GetHitW() / 2), o->GetHitY() + (o->GetHitH() / 2));
        }

        if (o->GetMyType() == HitObjectBase::HitObjectType::Item) {//���W�A�C�e���̃J�E���g
            Game::itemCountUp();
        }

        });

    std::for_each(objectList.begin(), objectList.end(), [](Obj& o) {
        o->update();

        if (ViewData::viewTarget == o) {//�^�[�Q�b�g�������ꍇ�A�`����W�����W�l�Ɏw��
            ViewData::SetRenderPos(o->GetPosX() - (ViewData::window_w / 2), o->GetPosY());

            //�}�b�v�z��O�Ɉړ����Ȃ��悤�ʒu�𐧌�
            //X�␳
            if (ViewData::GetRenderPosX() <= 0) ViewData::SetRenderPos(0, ViewData::GetRenderPosY());
            else if (ViewData::GetRenderPosX() >= Map::width * Map::blockSize - ViewData::window_w)
                ViewData::SetRenderPos(Map::width * Map::blockSize - ViewData::window_w, ViewData::GetRenderPosY());

            //Y�␳
            if (ViewData::GetRenderPosY() <= 0) ViewData::SetRenderPos(ViewData::GetRenderPosX(), 0);
            else if (ViewData::GetRenderPosY() >= Map::height * Map::blockSize - ViewData::window_h)
                ViewData::SetRenderPos(ViewData::GetRenderPosX(), Map::height * Map::blockSize - ViewData::window_h);
        }

        });

    // �����蔻��
    //�܂��A�S���̃I�u�W�F�N�g�̒�����AHitObjectBase�p����T��
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [&](hObj& me) {
        //����������s��
        std::for_each(hitObjectList.begin(), hitObjectList.end(), [&](hObj& you) {
            //�����̃q�b�g�^�C�v�Ɣ�����s���^�C�v����v�����ꍇ
            if (me->GetHitType() == you->GetMyType()) {
                //�q�b�g���Ă��邩����
                if (me->HitJudge(*you)) {
                    //�q�b�g�����ꍇ�͏������s��
                    me->HitMove(*you);
                }
            }
            else if (me->GetHitType() == HitObjectBase::HitObjectType::AllHit) {//�ume�v���uAllHit�v�Ȃ�q�b�g���Ă��邩�𔻒�
                //�q�b�g���Ă��邩����
                if (me->HitJudge(*you)) {
                    //�q�b�g�����ꍇ�͏������s��
                    me->HitMove(*you);
                }
            }
        });
     });

    //�����ׂ��I�u�W�F�N�g�̍폜
    std::list<Obj>::iterator endO = std::remove_if(objectList.begin(), objectList.end(), [](Obj& o) {
        if (o->GetRemoveFlag()) {//�t���O�Q��
            o->finalize();
            return true;
        }
        return false;
        });
    objectList.erase(endO, objectList.end());//�v�f�̍폜�idelete�ł͂Ȃ��j

    //��Ɠ��������HitObject�ɂ��s��
    std::list<hObj>::iterator endHO = std::remove_if(hitObjectList.begin(), hitObjectList.end(), [](hObj& ho) {
        if (ho->GetRemoveFlag()) {//�t���O�Q��
            ho->finalize();
            return true;
        }
        return false;
        });
   
    hitObjectList.erase(endHO, hitObjectList.end());
}

void GameScene::Draw() {
    //�}�b�v�̕`��i�}�b�v�̓I�u�W�F�N�g�ł͂Ȃ��j
    Map::DrawMap();

    //�I�u�W�F�N�g���Ƃ̕`�揈��
    std::for_each(hitObjectList.begin(), hitObjectList.end(), [](hObj& o) {o->draw(); });
    //�G�t�F�N�g����ɕ`�悷��
    std::for_each(objectList.begin(), objectList.end(), [](Obj& o) {o->draw(); });
}


//AddList.h���̏����@�����蔻��������Ȃ��I�u�W�F�N�g�����X�g�ɒǉ�
void Game::AddList_AddFront(const Obj& obj) {
    objectList.push_front(obj);
}
void Game::AddList_AddBack(const Obj& obj) {
    objectList.push_back(obj);
}

//AddList.h���̏����@�����蔻������I�u�W�F�N�g�����X�g�ɒǉ�
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