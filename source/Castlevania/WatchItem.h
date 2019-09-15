#pragma once
#include "ItemObject.h"
#define ITEM_WATCH_POINT 0
#define ITEM_WATCH_BBOX_WIDTH 30
#define ITEM_WATCH_BBOX_HEIGHT 32
enum class WatchItemAnim {
	IDLE = 2600
};

class CWatchItem :public CItemObject {

public:
	CWatchItem() :CItemObject(ITEM_WATCH_POINT) { prevAnim = currentAnim = (int)WatchItemAnim::IDLE; };
	CWatchItem(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};