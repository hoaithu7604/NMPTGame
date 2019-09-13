#pragma once
#include "ItemObject.h"
#define ITEM_DAGGER_POINT 0
#define ITEM_DAGGER_BBOX_WIDTH 32
#define ITEM_DAGGER_BBOX_HEIGHT 18
enum class DaggerItemAnim {
	IDLE = 1000
};

class CDaggerItem :public CItemObject {

public:
	CDaggerItem() :CItemObject(ITEM_DAGGER_POINT) { prevAnim = currentAnim = (int)DaggerItemAnim::IDLE; };
	CDaggerItem(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};