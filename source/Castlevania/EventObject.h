#pragma once
#include "GameObject.h"
class CEventObject: public CGameObject
{
protected:
	float width;
	float height;
	bool isTriggering = false;
public:
	CEventObject() :CGameObject() { state = GAMEOBJECT_STATE_UPDATE_ONLY;}
	CEventObject(float x, float y, float width, float height);
	bool IsTriggering() { return isTriggering; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Trigger() {}
	virtual bool ShouldTrigger() { return isTriggering; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};