#pragma once
#include "EffectObject.h"
#define POINT_EFFECT_BBOX_WIDTH 30
#define POINT_EFFECT_BBOX_HEIGHT 10
#define POINT_EFFECT_LAST_TIME 1000
enum class PointEffectAnim {
	p100=3400,
	p300,
	p700,
	p1000
};
class CPointEffect : public CEffectObject
{

public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CPointEffect(float x, float y, int point);
};