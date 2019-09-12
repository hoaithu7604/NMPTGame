#pragma once
#include "Timer.h"
#define AUTO_MOVER_MODE_DEFAULT 0 //disable if player do action
#define AUTO_MOVER_MODE_FORCED 1 //disable player control, can't deactive outside this class
#define AUTO_MOVER_TYPE_DEFAULT 0 // stop when simon reach target point
#define AUTO_MOVER_TYPE_TIMED 1 //  stop after certain time
#define MIN_DISTANCE 5 
class CAutoMover
{
	float targetX;
	float targetY;
	float speed;
	int mode;
	int type;
	CTimer timer;
	bool isActive = false;
public:
	CAutoMover() {};
	bool IsActive() { return isActive; }
	void Active(int mode = -1,int type = -1);
	void Deactive() { if (mode!=AUTO_MOVER_MODE_FORCED) isActive = false; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetMode(int mode) { this->mode = mode; }
	void SetType(int type) { this->type = type; }
	void SetTarget(float x, float y); 
	void SetTime(DWORD t); 
	void Update(DWORD dt);
	bool GetVelocity(float&vx, float&vy,DWORD dt); //true if simon reach target point
};