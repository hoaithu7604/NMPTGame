#pragma once
#include "MagicCrystal.h"
#include "Simon.h"
void CMagicCrystal::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_MAGIC_CRYSTAL_BBOX_WIDTH;
	bottom = top + ITEM_MAGIC_CRYSTAL_BBOX_HEIGHT;
}
CMagicCrystal::CMagicCrystal(float x, float y)
	:CItemObject(ITEM_MAGIC_CRYSTAL_POINT)
{
	currentAnim = (int)MagicCrystalAnimID::IDLE;
	prevAnim = (int)MagicCrystalAnimID::IDLE;
	this->x = x - ITEM_MAGIC_CRYSTAL_BBOX_WIDTH / 2;
	this->y = y - ITEM_MAGIC_CRYSTAL_BBOX_HEIGHT / 2;
}
void CMagicCrystal::GetReward()
{
	CSimon::GetInstance()->AddHealth(ITEM_MAGIC_CRYSTAL_HEALTH_VALUE);
	CItemObject::GetReward();
}