#pragma once
#include "EventObject.h"
#define AUTO_WALK_SPEED 0.05f
#define MIN_DISTANCE 5
class CAutoWalkEvent : public CEventObject
{
	float targetX;
	float targetY;
public:
	CAutoWalkEvent() : CEventObject() {}
	CAutoWalkEvent(float x, float y, float width, float height) :CEventObject(x, y, width, height) {}
	void SetTargetPos(float x, float y) { targetX = x; targetY = y; }
	virtual void Trigger();
	virtual bool ShouldTrigger();
};