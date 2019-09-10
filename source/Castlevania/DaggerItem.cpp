#pragma once
#include "DaggerItem.h"
#include "Dagger.h"
void CDaggerItem::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_DAGGER_BBOX_WIDTH;
	bottom = top + ITEM_DAGGER_BBOX_HEIGHT;
}
CDaggerItem::CDaggerItem(float x, float y)
	:CItemObject(ITEM_DAGGER_POINT)
{
	currentAnim = (int)DaggerItemAnim::IDLE;
	prevAnim = (int)DaggerItemAnim::IDLE;
	this->x = x - ITEM_DAGGER_BBOX_WIDTH / 2;
	this->y = y - ITEM_DAGGER_BBOX_HEIGHT / 2;
}
void CDaggerItem::Render()
{
	if (isOnCamera()) CGameObject::Render();
}
void CDaggerItem::GetReward()
{
	CSimon::GetInstance()->ChangeWeapon(new CDagger());
	CItemObject::GetReward();
}