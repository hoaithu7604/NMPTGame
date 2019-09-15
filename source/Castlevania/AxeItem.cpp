#pragma once
#include "AxeItem.h"
#include "Axe.h"
void CAxeItem::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_AXE_BBOX_WIDTH;
	bottom = top + ITEM_AXE_BBOX_HEIGHT;
}
CAxeItem::CAxeItem(float x, float y)
	:CItemObject(ITEM_AXE_POINT)
{
	currentAnim = (int)AxeItemAnim::IDLE;
	prevAnim = (int)AxeItemAnim::IDLE;
	this->x = x - ITEM_AXE_BBOX_WIDTH / 2;
	this->y = y - ITEM_AXE_BBOX_HEIGHT / 2;
}
void CAxeItem::GetReward()
{
	CSimon::GetInstance()->ChangeWeapon(new CAxe());
	CItemObject::GetReward();
}