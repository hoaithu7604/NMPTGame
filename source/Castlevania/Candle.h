#pragma once
#include "ItemHolder.h"
#define CANDLE_HEALTH_DEFAULT 1;
#define CANDLE_BBOX_WIDTH 16
#define CANDLE_BBOX_HEIGHT 26
enum class CandleAnimID {
	IDLE = 1100
};
class CCandle : public CItemHolder
{

public:
	CCandle() :CItemHolder() { health = CANDLE_HEALTH_DEFAULT; currentAnim = (int)CandleAnimID::IDLE; prevAnim = (int)CandleAnimID::IDLE; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};