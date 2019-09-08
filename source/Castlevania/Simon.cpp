#pragma once
#include "Simon.h"
#include "UnseenForce.h"
#include "Torch.h"
#include "FlameEffect.h"
#include "BigHeart.h"
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
	heart = SIMON_HEART_DEFAULT;
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

	if (isJumping)
	{
		if (vy >= 0)
		{
			isCrouching = false;
			vy += SIMON_FALLING_SPEED * dt;
		}
		else 
		{
			if (this->rope->isActive())
				isCrouching = false;
			vy += SIMON_JUMPING_FALLING_SPEED * dt;
		}

	}
	else vy += SIMON_FALLING_SPEED * dt;
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
		
		//if (nx == 0) x += dx; 
		//if (ny >= 0) y += dy; //ignore collision above
		bool should_x_change = true;
		bool should_y_change = true;
		//
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CUnseenForce *>(e->obj))
			{
				if (e->ny < 0) 
				{
					should_y_change = false;
					if (isJumping)
					{
						isJumping = false;
						vx = 0;
					}
					vy = 0;
					y += e->t * dy + ny * AVOID_OVERLAPPLING_FORCE;
				}
				if (e->nx != 0) 
				{
					x += e->t * dx + nx * AVOID_OVERLAPPLING_FORCE;		
					vx = 0;
					should_x_change = false;
				}
			}
			else if (dynamic_cast<CTorch *>(e->obj))
			{
				//do nothing
				DebugOut(L"[INFO] TOUCHED TORCH");
			}
			else if (dynamic_cast<CFlameEffect*>(e->obj)) 
			{
				DebugOut(L"[INFO] TOUCHED FLAME EFFECT");
			}
			else if (dynamic_cast<CBigHeart*>(e->obj))
			{
				DebugOut(L"[INFO] TOUCHED BIG HEART");
				dynamic_cast<CBigHeart*>(e->obj)->GetReward();
				
			}
		}
		if (should_x_change) x += dx;
		if (should_y_change) y += dy;



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
	switch (action) {
	case Action::ATTACK:
		if (!attack_timer.isActive())
		{
			attack_timer.Active();
			
			this->rope->Active();
			if (!isJumping) this->vx = 0;
		}
		break;
	}
	if (isJumping) return;
	//------------------------------
	switch (action) {
		case Action::JUMP:
			Jump();
			break;
		case Action::CROUCH:
			if (!isCrouching)
			{
				this->isCrouching = true;
				this->vx = 0;
				y += SIMON_IDLE_BBOX_HEIGHT - SIMON_CROUCHING_BBOX_HEIGHT;
			}
			break;
		case Action::WALK_RIGHT:
			StandUp();
			this->nx = 1;
			this->vx = SIMON_WALKING_SPEED * this->nx;
			break;
		case Action::WALK_LEFT:
			StandUp();
			this->nx = -1;
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
	else if (isJumping)
	{
		if (this->vy < 0) {
			currentAnim = nx > 0 ? (int)SimonAnimID::CROUCH_RIGHT : (int)SimonAnimID::CROUCH_LEFT;
		}
		else
		{
			currentAnim = nx > 0 ? (int)SimonAnimID::IDLE_RIGHT : (int)SimonAnimID::IDLE_LEFT;
		}
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
void CSimon::Jump()
{
	//can't jump if simon is crouching or attacking or jumping 
	if (!isJumping&&!isCrouching && !this->rope->isActive())
	{
		isJumping = true;
		isCrouching = true;
		this->vy = -SIMON_JUMPING_SPEED;
		y += SIMON_IDLE_BBOX_HEIGHT - SIMON_CROUCHING_BBOX_HEIGHT;
	}
}
void CSimon::Focus()
{
	float top, left, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	//focus camera to the center point of bbox
	camera->Focus(int((left+right)/2), int((top + bottom)/ 2));
}