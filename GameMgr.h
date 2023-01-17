#pragma once

namespace Game {
	//アイテム（巻物）
	extern int clearItemCounter;//残りアイテム数
	extern void itemCountUp();
	extern void itemCountReset();
	extern bool clearJudge();
}