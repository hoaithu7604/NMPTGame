#pragma once
#include "EffectObject.h"
#define BUBBLE_EFFECT_BBOX_WIDTH 14
#define BUBBLE_EFFECT_BBOX_HEIGHT 16
#define BUBBLE_EFFECT_LAST_TIME 2000
#define BUBBLE_EFFECT_SPEED 0.3f
#define BUBBLE_EFFECT_FALLING_SPEED 0.001f
#define BUBBLE_EFFECT_COUNT 3
enum class BubbleEffectAnim {
	IDLE = 3200
};
class CBubbleEffect : public CEffectObject
{
	float vx, vy; 
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CBubbleEffect(float x, float y);
	static void CreateEffect(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};