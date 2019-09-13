#pragma once
#include "EffectObject.h"
#define CROSSFLAME_EFFECT_BBOX_WIDTH 16
#define CROSSFLAME_EFFECT_BBOX_HEIGHT 20
#define CROSSFLAME_EFFECT_LAST_TIME 200
#define CROSSFLAME_SPAWNABLE_DISTANCE 20.f
enum class CrossFlameEffectAnim {
	IDLE = 1600
};
class CCrossFlameEffect : public CEffectObject
{

public:
	CCrossFlameEffect();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CCrossFlameEffect(float x, float y);
};