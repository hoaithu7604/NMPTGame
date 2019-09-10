#pragma once
#include "EventObject.h"

class CTeleportEvent :public CEventObject
{
	float targetX;
	float targetY;
public:
	CTeleportEvent() : CEventObject() {}
	CTeleportEvent(float x, float y, float width, float height) :CEventObject(x, y, width, height) {}
	void SetTargetPos(float x, float y) { targetX = x; targetY = y; }
	virtual void Trigger();
	virtual bool ShouldTrigger();
};