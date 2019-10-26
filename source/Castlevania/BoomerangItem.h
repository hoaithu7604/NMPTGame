#pragma once
#include "ItemObject.h"
#define ITEM_BOOMERANG_POINT 0
#define ITEM_BOOMERANG_BBOX_WIDTH 28
#define ITEM_BOOMERANG_BBOX_HEIGHT 28
enum class BoomerangItemAnim {
	IDLE = 3300
};

class CBoomerangItem :public CItemObject {

public:
	CBoomerangItem() :CItemObject(ITEM_BOOMERANG_POINT) { prevAnim = currentAnim = (int)BoomerangItemAnim::IDLE; };
	CBoomerangItem(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};