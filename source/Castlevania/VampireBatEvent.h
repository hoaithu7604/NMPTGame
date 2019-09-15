#pragma once
#include "EventObject.h"
#include "UnseenForce.h"
#include "VampireBat.h"
#include "Timer.h"
#define WAKE_DELAY 10000
#define WALL_SIZE 50
class CVampireBatEvent :public CEventObject
{
	float cameraX;
	float cameraY;
	CUnseenForce*left;
	CUnseenForce*top;
	CUnseenForce*right;
	CUnseenForce*bottom;
	CVampireBat* bat;
	CTimer wakeDelayTimer;
	bool isTriggered;
public:
	CVampireBatEvent(float x, float y, float width, float height,
		float cameraX,float cameraY,float batX,float batY);
	void DeactiveWall();
	void ActiveWall();
	virtual void Trigger();
	virtual bool ShouldTrigger();
};
