#pragma once
#include "WatchItem.h"
#include "Watch.h"
void CWatchItem::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_WATCH_BBOX_WIDTH;
	bottom = top + ITEM_WATCH_BBOX_HEIGHT;
}
CWatchItem::CWatchItem(float x, float y)
	:CItemObject(ITEM_WATCH_POINT)
{
	currentAnim = (int)WatchItemAnim::IDLE;
	prevAnim = (int)WatchItemAnim::IDLE;
	this->x = x - ITEM_WATCH_BBOX_WIDTH / 2;
	this->y = y - ITEM_WATCH_BBOX_HEIGHT / 2;
}
void CWatchItem::GetReward()
{
	CSimon::GetInstance()->ChangeWeapon(new CWatch());
	CItemObject::GetReward();
}