#pragma once
#include "ItemObject.h"
#define ITEM_NIRENSYA_BBOX_WIDTH 28
#define ITEM_NIRENSYA_BBOX_HEIGHT 28
#define ITEM_NIRENSYA_POINT 0
enum class NirensyaAnimID {
	IDLE = 2900
};
class CNirensya : public CItemObject
{
public:
	CNirensya(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};