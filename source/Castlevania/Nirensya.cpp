#pragma once
#include "Nirensya.h"
#include "UnseenForce.h"
#include "Simon.h"
void CNirensya::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_NIRENSYA_BBOX_WIDTH;
	bottom = top + ITEM_NIRENSYA_BBOX_HEIGHT;
}
CNirensya::CNirensya(float x, float y)
	:CItemObject(ITEM_NIRENSYA_POINT)
{
	currentAnim = (int)NirensyaAnimID::IDLE;
	prevAnim = (int)NirensyaAnimID::IDLE;
	this->x = x - ITEM_NIRENSYA_BBOX_WIDTH / 2;
	this->y = y - ITEM_NIRENSYA_BBOX_HEIGHT / 2;
}
void CNirensya::GetReward()
{
	//
	CSimon::GetInstance()->SetPowerUp(PowerUp::NIRENSYA);
	CItemObject::GetReward();
}