#pragma once
#include "EffectObject.h"
#define FIREBOMB_EFFECT_DURATION 3000
#define FIREBOMB_EFFECT_BBOX_WIDTH 32
#define FIREBOMB_EFFECT_BBOX_HEIGHT 26
enum class FireBombFireEffectAnimID
{
	IDLE = 1903,
};
class CFireBombFireEffect : public CEffectObject
{
	int damage;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CFireBombFireEffect(float x, float y, int damage);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
};