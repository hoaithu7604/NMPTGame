#pragma once
#include "EffectObject.h"
#define FLAME_EFFECT_BBOX_WIDTH 16
#define FLAME_EFFECT_BBOX_HEIGHT 30
#define FLAME_EFFECT_LAST_TIME 200
enum class FlameEffectAnim {
	IDLE = 400
};
class CFlameEffect : public CEffectObject
{

public:
	CFlameEffect() { currentAnim = (int)FlameEffectAnim::IDLE; prevAnim = (int)FlameEffectAnim::IDLE; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CFlameEffect(float x, float y);
	
};