#pragma once
#include "../base/HitObjectBase.h"

/// <summary>
/// 
/// マップは関数でのみ操作可能。直接の操作は禁止
/// 
/// </summary>

namespace Map {

	extern const int width;
	extern const int height;
	extern int blockSize;
	extern int mapNum;

	extern void LoadMapData(int gn_);

	extern int GetMapChip(int y, int x);

	extern void DrawMap();

	extern bool MapCheckHit(float hitboxX, float hitboxY, float hitboxW, float hitboxH);
}