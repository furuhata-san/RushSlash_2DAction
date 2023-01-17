#pragma once

//すべてのリストシーンで使用する可能性のあるもの
#include "Object.h"
#include "HitObjectBase.h"
#include <memory>

//シェアポインタ
typedef std::shared_ptr<Object> Obj;
typedef std::shared_ptr<HitObjectBase> hObj;

namespace Game {
	extern void AddList_AddFront(const Obj& obj);
	extern void AddList_AddBack(const Obj& obj);
	extern void AddList_AddFront(const hObj& hobj);
	extern void AddList_AddBack(const hObj& hobj);
}
