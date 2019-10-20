#pragma once
#include "EffectObject.h"
#define BRICK_BREAKING_EFFECT_BBOX_WIDTH 14
#define BRICK_BREAKING_EFFECT_BBOX_HEIGHT 16
#define BRICK_BREAKING_EFFECT_LAST_TIME 2000
#define BRICK_BREAKING_EFFECT_SPEED 0.3f
#define BRICK_BREAKING_EFFECT_FALLING_SPEED 0.001f
enum class BrickBreakingEffectAnim {
	IDLE = 1800
};
class CBrickBreakingEffect : public CEffectObject
{
	float vx, vy; // damn it i didn't think effect object will need to be moved >.> so lazy to to change it now so just use this instead
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CBrickBreakingEffect(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};