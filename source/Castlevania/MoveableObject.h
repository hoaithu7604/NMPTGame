#pragma once
#include "GameObject.h"
#define AVOID_OVERLAPPLING_FORCE 0.2f
enum class Action
{
	IDLE,
	WALK_RIGHT,
	WALK_LEFT,
	ATTACK
};
//class for objects which are capable to move
class CMoveableObject : public CGameObject
{
protected:
	//velocity
	float vx; 
	float vy;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	DWORD dt;
public:
	CMoveableObject();
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx, vy = this->vy; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) {};
	virtual void Render() {};
};