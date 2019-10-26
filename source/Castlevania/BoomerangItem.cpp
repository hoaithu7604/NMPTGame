#pragma once
#include "BoomerangItem.h"
#include "Boomerang.h"
void CBoomerangItem::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_BOOMERANG_BBOX_WIDTH;
	bottom = top + ITEM_BOOMERANG_BBOX_HEIGHT;
}
CBoomerangItem::CBoomerangItem(float x, float y)
	:CItemObject(ITEM_BOOMERANG_POINT)
{
	currentAnim = (int)BoomerangItemAnim::IDLE;
	prevAnim = (int)BoomerangItemAnim::IDLE;
	this->x = x - ITEM_BOOMERANG_BBOX_WIDTH / 2;
	this->y = y - ITEM_BOOMERANG_BBOX_HEIGHT / 2;
}
void CBoomerangItem::GetReward()
{
	CSimon::GetInstance()->ChangeWeapon(new CBoomerang());
	CItemObject::GetReward();
}