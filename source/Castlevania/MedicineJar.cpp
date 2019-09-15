#pragma once
#include "MedicineJar.h"
void CMedicineJar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_MEDICINEJAR_BBOX_WIDTH;
	bottom = top + ITEM_MEDICINEJAR_BBOX_HEIGHT;
}
CMedicineJar::CMedicineJar(float x, float y)
	:CItemObject(ITEM_MEDICINEJAR_POINT)
{
	currentAnim = (int)MedicineJarAnimID::IDLE;
	prevAnim = (int)MedicineJarAnimID::IDLE;
	this->x = x - ITEM_MEDICINEJAR_BBOX_WIDTH / 2;
	this->y = y - ITEM_MEDICINEJAR_BBOX_HEIGHT / 2;
}
void CMedicineJar::GetReward()
{
	CSimon::GetInstance()->SetInvul(ITEM_MEDICINEJAR_DURATION);
	CItemObject::GetReward();
}