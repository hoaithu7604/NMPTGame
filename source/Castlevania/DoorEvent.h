#pragma once
#include "EventObject.h"
#include "Gate.h"
#include "Timer.h"
#include "UnseenForce.h"
#define DOOR_OPEN_DELAY 1500
#define DOOR_EVENT_SPEED 0.075f
#define WALK_DELAY 1000
#define DOOR_CLOSE_DELAY 2200
#define CAMERA_RETURN_DELAY 2000
#define FINISH_DELAY 2000
class CDoorEvent : public CEventObject
{
	//where to lock camera to
	float cameraX;
	float cameraY; 
	//pointer to the gate
	CGate* gate; 
	CUnseenForce* dummyGate;
	//where simon walks to
	float targetX;
	float targetY;
	//where to put the camera when the event end
	float finishX;
	float finishY;

	CTimer openDelayTimer;
	CTimer walkDelayTimer;
	CTimer closeDelayTimer;
	CTimer cameraReturnTimer;
	CTimer finishDelayTimer;
public:
	CDoorEvent(float x, float y, float width, float height, 
		float cameraX, float cameraY, float doorX, float doorY, 
		float targetX, float targetY, float finishX, float finishY);
	virtual bool ShouldTrigger();
	virtual void Trigger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};