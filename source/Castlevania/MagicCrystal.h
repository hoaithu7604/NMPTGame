#pragma once
#include "ItemObject.h"
#define ITEM_MAGIC_CRYSTAL_BBOX_WIDTH 32
#define ITEM_MAGIC_CRYSTAL_BBOX_HEIGHT 32
#define ITEM_MAGIC_CRYSTAL_POINT 0
#define ITEM_MAGIC_CRYSTAL_HEALTH_VALUE 20
enum class MagicCrystalAnimID {
	IDLE = 3100
};
class CMagicCrystal : public CItemObject
{
public:
	CMagicCrystal() :CItemObject(ITEM_MAGIC_CRYSTAL_POINT) { currentAnim = (int)MagicCrystalAnimID::IDLE; prevAnim = (int)MagicCrystalAnimID::IDLE; };
	CMagicCrystal(float x, float y);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};