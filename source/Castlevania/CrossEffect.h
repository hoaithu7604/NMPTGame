#pragma once
#include "EffectObject.h"
#define CROSS_EFFECT_LAST_TIME 500
#define CROSS_EFFECT_DAMAGE 1000
//a dummy object to make thing easier :/
class CCrossEffect : public CEffectObject
{
	bool changeBG = true;
public:
	CCrossEffect():CEffectObject(CROSS_EFFECT_LAST_TIME) {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};