#pragma once

//���ׂẴ��X�g�V�[���Ŏg�p����\���̂������
#include "Object.h"
#include "HitObjectBase.h"
#include <memory>

//�V�F�A�|�C���^
typedef std::shared_ptr<Object> Obj;
typedef std::shared_ptr<HitObjectBase> hObj;

namespace Game {
	extern void AddList_AddFront(const Obj& obj);
	extern void AddList_AddBack(const Obj& obj);
	extern void AddList_AddFront(const hObj& hobj);
	extern void AddList_AddBack(const hObj& hobj);
}
