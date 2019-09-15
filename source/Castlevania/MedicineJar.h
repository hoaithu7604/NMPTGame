#pragma once
#include "ItemObject.h"
#define ITEM_MEDICINEJAR_BBOX_WIDTH 26
#define ITEM_MEDICINEJAR_BBOX_HEIGHT 32
#define ITEM_MEDICINEJAR_POINT 0
#define ITEM_MEDICINEJAR_DURATION 5000
enum class MedicineJarAnimID {
	IDLE = 2700
};
class CMedicineJar : public CItemObject
{
public:
	CMedicineJar() :CItemObject(ITEM_MEDICINEJAR_POINT) { currentAnim = (int)MedicineJarAnimID::IDLE; prevAnim = (int)MedicineJarAnimID::IDLE; };
	CMedicineJar(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};