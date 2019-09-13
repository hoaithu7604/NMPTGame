#pragma once
#include "ItemObject.h"
#define MONEYBAG_TIER_ONE 1
#define MONEYBAG_TIER_TWO 2
#define MONEYBAG_TIER_THREE 3
#define MONEYBAG_TIER_FOUR 4
#define MONEYBAG_TIER_ONE_POINT 100
#define MONEYBAG_TIER_TWO_POINT 300
#define MONEYBAG_TIER_THREE_POINT 700
#define MONEYBAG_TIER_FOUR_POINT 1000
#define MONEYBAG_BBOX_WIDTH 30
#define MONEYBAG_BBOX_HEIGHT 30
enum class MoneyBagAnimID
{
	TIER_ONE=1500,
	TIER_TWO,
	TIER_THREE,
	TIER_FOUR
};
class CMoneyBag :public CItemObject
{
public:
	CMoneyBag(float x, float y, int tier);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};