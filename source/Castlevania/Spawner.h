#pragma once
#include "GameObject.h"
#include "Timer.h"
class CSpawner : public CGameObject
{
protected:
	float width;
	float height;
	CTimer cooldown_timer;
public:
	CSpawner() :CGameObject() { state = GAMEOBJECT_STATE_UPDATE_ONLY; } 
	CSpawner(float x, float y, float width, float height);
	virtual bool ShouldSpawn() { return false; }
	virtual void Spawn() {}
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};