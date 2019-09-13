#pragma once
#include "Cross.h"
#include "CrossEffect.h"
void CCross::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_CROSS_BBOX_WIDTH;
	bottom = top + ITEM_CROSS_BBOX_HEIGHT;
}
CCross::CCross(float x, float y)
	:CItemObject(ITEM_CROSS_POINT)
{
	currentAnim = (int)CrossAnimID::IDLE;
	prevAnim = (int)CrossAnimID::IDLE;
	this->x = x - ITEM_CROSS_BBOX_WIDTH / 2;
	this->y = y - ITEM_CROSS_BBOX_HEIGHT / 2;
}
void CCross::GetReward()
{
	CGameObject::AddObject(new CCrossEffect());
	CItemObject::GetReward();
}