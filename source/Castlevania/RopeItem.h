#pragma once
#include "ItemObject.h"
#define ITEM_ROPEITEM_BBOX_WIDTH 32
#define ITEM_ROPEITEM_BBOX_HEIGHT 32
#define ITEM_ROPEITEM_POINT 0
enum class CRopeItemAnim {
	IDLE=600
};
class CRopeItem : public CItemObject
{

public:
	CRopeItem() :CItemObject(ITEM_ROPEITEM_POINT) { currentAnim = (int)CRopeItemAnim::IDLE; prevAnim = (int)CRopeItemAnim::IDLE;}
	CRopeItem(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
};