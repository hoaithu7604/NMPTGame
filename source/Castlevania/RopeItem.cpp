#include "RopeItem.h"
#include "Simon.h"
void CRopeItem::GetReward() 
{
	CSimon::GetInstance()->IncreaseRopeLevel();
	CItemObject::GetReward();
}
void CRopeItem::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = left + ITEM_ROPEITEM_BBOX_WIDTH;
	bottom = top + ITEM_ROPEITEM_BBOX_HEIGHT;
}
CRopeItem::CRopeItem(float x, float y)
	:CItemObject(ITEM_ROPEITEM_POINT)
{
	this->x = x - ITEM_ROPEITEM_BBOX_WIDTH / 2;
	this->y = y - ITEM_ROPEITEM_BBOX_HEIGHT / 2;
	currentAnim = (int)CRopeItemAnim::IDLE;
	prevAnim = (int)CRopeItemAnim::IDLE;
}
