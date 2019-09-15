#pragma once
#include "ItemObject.h"
#define ITEM_PORKCHOP_BBOX_WIDTH 32
#define ITEM_PORKCHOP_BBOX_HEIGHT 32
#define ITEM_PORKCHOP_POINT 0
#define ITEM_PORKCHOP_HEALTH_VALUE 5
enum class PorkChopAnimID {
	IDLE = 2500
};
class CPorkChop : public CItemObject
{
public:
	CPorkChop() :CItemObject(ITEM_PORKCHOP_POINT) { currentAnim = (int)PorkChopAnimID::IDLE; prevAnim = (int)PorkChopAnimID::IDLE; };
	CPorkChop(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};