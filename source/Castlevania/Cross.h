#pragma once
#include "ItemObject.h"
#define ITEM_CROSS_BBOX_WIDTH 32
#define ITEM_CROSS_BBOX_HEIGHT 32
#define ITEM_CROSS_POINT 0
enum class CrossAnimID {
	IDLE = 2000
};
class CCross : public CItemObject
{
public:
	CCross() :CItemObject(ITEM_CROSS_POINT) { currentAnim = (int)CrossAnimID::IDLE; prevAnim = (int)CrossAnimID::IDLE; };
	CCross(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};