#pragma once
#include "PorkChop.h"
#include "UnseenForce.h"
#include "Simon.h"
void CPorkChop::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_PORKCHOP_BBOX_WIDTH;
	bottom = top + ITEM_PORKCHOP_BBOX_HEIGHT;
}
CPorkChop::CPorkChop(float x, float y)
	:CItemObject(ITEM_PORKCHOP_POINT)
{
	currentAnim = (int)PorkChopAnimID::IDLE;
	prevAnim = (int)PorkChopAnimID::IDLE;
	this->x = x - ITEM_PORKCHOP_BBOX_WIDTH / 2;
	this->y = y - ITEM_PORKCHOP_BBOX_HEIGHT / 2;
}
void CPorkChop::GetReward()
{
	CSimon::GetInstance()->AddHealth(ITEM_PORKCHOP_HEALTH_VALUE);
	CItemObject::GetReward();
}