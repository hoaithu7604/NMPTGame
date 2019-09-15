#pragma once
#include "EventObject.h"

class CItemSpawnEvent :public CEventObject
{
	float targetX;
	float targetY;
	//should have rework EventObject for 1 time event later
	float isTriggered;
public:
	CItemSpawnEvent() : CEventObject() {}
	CItemSpawnEvent(float x, float y, float width, float height) :CEventObject(x, y, width, height) { isTriggered = false; }
	void SetTargetPos(float x, float y) { targetX = x; targetY = y; }
	virtual void Trigger();
	virtual bool ShouldTrigger();
};