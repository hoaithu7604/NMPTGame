#pragma once
#include "ItemObject.h"
#define ITEM_AXE_POINT 0
#define ITEM_AXE_BBOX_WIDTH 30
#define ITEM_AXE_BBOX_HEIGHT 28
enum class AxeItemAnim {
	IDLE = 2800
};

class CAxeItem :public CItemObject {

public:
	CAxeItem() :CItemObject(ITEM_AXE_POINT) { prevAnim = currentAnim = (int)AxeItemAnim::IDLE; };
	CAxeItem(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};