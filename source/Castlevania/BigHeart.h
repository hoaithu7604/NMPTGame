#pragma once
#include "ItemObject.h"
#define ITEM_BIGHEART_BBOX_WIDTH 24
#define ITEM_BIGHEART_BBOX_HEIGHT 20
#define ITEM_BIGHEART_POINT 0
#define ITEM_BIGHEART_HEART_VALUE 5
enum class BigHeartAnimID {
	IDLE = 500
};
class CBigHeart : public CItemObject
{
public:
	CBigHeart() :CItemObject(ITEM_BIGHEART_POINT) { currentAnim = (int)BigHeartAnimID::IDLE; prevAnim = (int)BigHeartAnimID::IDLE;};
	CBigHeart(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};