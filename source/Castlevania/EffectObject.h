#pragma once
#include "GameObject.h"
#include "Timer.h"
#define DEFAULT_LAST_TIME 1000
class CEffectObject:public CGameObject
{
protected:
	CTimer timer;
public:
	CEffectObject();
	CEffectObject(DWORD time);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};