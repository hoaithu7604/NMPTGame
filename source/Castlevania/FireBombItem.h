#pragma once
#include "ItemObject.h"
#define ITEM_FIREBOMB_POINT 0
#define ITEM_FIREBOMB_BBOX_WIDTH 32
#define ITEM_FIREBOMB_BBOX_HEIGHT 32
enum class FireBombItemAnim {
	IDLE = 1900
};

class CFireBombItem :public CItemObject {

public:
	CFireBombItem() :CItemObject(ITEM_FIREBOMB_POINT) { prevAnim = currentAnim = (int)FireBombItemAnim::IDLE; };
	CFireBombItem(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};