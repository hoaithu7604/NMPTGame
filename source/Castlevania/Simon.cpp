#pragma once
#include "Simon.h"
CSimon * CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon() 
	:CMoveableObject()
{
	attack_timer.SetTime(SIMON_ATTACK_COOLDOWN);

	isJumping = false;
	isCrouching = false;
	rope = new CSimonRope();
	currentAnim = (int)SimonAnimID::IDLE_RIGHT;
	prevAnim = (int)SimonAnimID::IDLE_RIGHT;
	camera = CCamera::GetInstance();
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (attack_timer.isActive()) {
		attack_timer.hasTicked();
	}


	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	vy += SIMON_FALLING_SPEED * dt;
	//
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * AVOID_OVERLAPPLING_FORCE;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * AVOID_OVERLAPPLING_FORCE;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//
		
	}

	//

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	this->rope->Update(x,y,nx,dt, coObjects);
	Focus();
	UpdateCurrentAnim();
}
void CSimon::Render() 
{
	CGameObject::Render(); 
	this->rope->Render();
}
void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	if (isCrouching)
	{
		right = x + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_CROUCHING_BBOX_HEIGHT;
	}
	else
	{
		right = x + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_IDLE_BBOX_HEIGHT;
	}
}
void CSimon::DoAction(Action action)
{
	//return if simon should not be able to do action here
	if (this->rope->isActive()) return; 
	
	//------------------------------
	switch (action) {
		case Action::ATTACK:
			if (!attack_timer.isActive())
			{
				attack_timer.Active();
				this->vx = 0;
				this->rope->Active();
			}
				break;
			
		case Action::CROUCH:
			if (!isCrouching)
			{
				this->isCrouching = true;
				this->vx = 0;
				y += SIMON_IDLE_BBOX_HEIGHT - SIMON_CROUCHING_BBOX_HEIGHT;
			}
			break;
		case Action::WALK_LEFT:
			StandUp();
			this->nx = -1;
			this->vx = SIMON_WALKING_SPEED * this->nx;
			break;
		case Action::WALK_RIGHT:
			StandUp();
			this->nx = 1;
			this->vx = SIMON_WALKING_SPEED * this->nx;
			break;
		case Action::IDLE:
			StandUp();
			this->vx = 0;
			break;
	}
}
void CSimon::UpdateCurrentAnim() 
{

	if (this->rope->isActive())
	{
		if (isCrouching) {
			currentAnim = nx > 0 ? (int)SimonAnimID::CROUCH_ATTACK_RIGHT : (int)SimonAnimID::CROUCH_ATTACK_LEFT;
		}
		else
		currentAnim = nx > 0 ? (int)SimonAnimID::ATTACK_RIGHT : (int)SimonAnimID::ATTACK_LEFT;
	}
	else if (isCrouching) {
		currentAnim = nx > 0 ? (int)SimonAnimID::CROUCH_RIGHT : (int)SimonAnimID::CROUCH_LEFT;
	}
	else if (vx != 0) {
		currentAnim = nx > 0 ? (int)SimonAnimID::WALK_RIGHT : (int)SimonAnimID::WALK_LEFT;
	}
	else
	{
		currentAnim = nx > 0 ? (int)SimonAnimID::IDLE_RIGHT : (int)SimonAnimID::IDLE_LEFT;
	}
}
void CSimon::StandUp()
{
	if (isCrouching)
	{
		isCrouching = false;
		y -= SIMON_IDLE_BBOX_HEIGHT - SIMON_CROUCHING_BBOX_HEIGHT;
	}
}
void CSimon::Focus()
{
	float top, left, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	//focus camera to the center point of bbox
	camera->Focus(int((left+right)/2), int((top + bottom)/ 2));
}