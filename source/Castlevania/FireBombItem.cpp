#pragma once
#include "FireBombItem.h"
#include "FireBomb.h"
void CFireBombItem::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_FIREBOMB_BBOX_WIDTH;
	bottom = top + ITEM_FIREBOMB_BBOX_HEIGHT;
}
CFireBombItem::CFireBombItem(float x, float y)
	:CItemObject(ITEM_FIREBOMB_POINT)
{
	currentAnim = (int)FireBombItemAnim::IDLE;
	prevAnim = (int)FireBombItemAnim::IDLE;
	this->x = x - ITEM_FIREBOMB_BBOX_WIDTH / 2;
	this->y = y - ITEM_FIREBOMB_BBOX_HEIGHT / 2;
}
void CFireBombItem::GetReward()
{
	CSimon::GetInstance()->ChangeWeapon(new CFireBomb());
	CItemObject::GetReward();
}