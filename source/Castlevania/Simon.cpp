#pragma once
#include "Simon.h"
#include "UnseenForce.h"
#include "Torch.h"
#include "FlameEffect.h"
#include "BigHeart.h"
#include "TimeFreezer.h"
#include "RopeItem.h"
#include "DaggerItem.h"
#include "TinyHeart.h"
CSimon * CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon() 
	:CMoveableObject()
{
	health = SIMON_HEALTH_DEFAULT;
	fabulous_timer.SetTime(SIMON_FABULOUS_DURATION);
	attack_timer.SetTime(SIMON_ATTACK_COOLDOWN);
	heart = SIMON_HEART_DEFAULT;
	isJumping = false;
	isCrouching = false;
	isUsingweapon = false;
	isControllable = true;
	weapon = NULL;
	rope = new CSimonRope();
	currentAnim = (int)SimonAnimID::IDLE_RIGHT;
	prevAnim = (int)SimonAnimID::IDLE_RIGHT;
	camera = CCamera::GetInstance();
}
// no collision events thing spawn on top of simon so let use this function
void CSimon::OverLappingLogic(vector<LPGAMEOBJECT>*coObjects,vector<LPGAMEOBJECT>*_objects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj=coObjects->at(i);
		if (dynamic_cast<CBigHeart *>(obj)&&isOverlapping(obj))
		{			
			dynamic_cast<CBigHeart*>(obj)->GetReward();
			DebugOut(L"[INFO] OVERLAPPING BIG HEART");			
		}
		else if (dynamic_cast<CTinyHeart *>(obj) && isOverlapping(obj))
		{
			dynamic_cast<CTinyHeart*>(obj)->GetReward();
			DebugOut(L"[INFO] OVERLAPPING TINY HEART");
		}
		else if (dynamic_cast<CRopeItem *>(obj) && isOverlapping(obj))
		{
			dynamic_cast<CRopeItem *>(obj)->GetReward();
			CTimeFreezer::GetInstance()->Active(SIMON_PICK_ITEM_FREEZE_TIME);
			fabulous_timer.Active();
			argb = RGB_RED;
			DebugOut(L"[INFO] OVERLAPPING ROPE ITEM");
		}
		else if (dynamic_cast<CTorch *>(obj)&&isOverlapping(obj))
		{
			DebugOut(L"[INFO] OVERLAPPING TORCH");
		}
		else if (dynamic_cast<CFlameEffect*>(obj)&&isOverlapping(obj))
		{
			DebugOut(L"[INFO] OVERLAPPING FLAME EFFECT");
		}		
		else if (dynamic_cast<CDaggerItem*>(obj) && isOverlapping(obj))
		{
			dynamic_cast<CDaggerItem *>(obj)->GetReward();
			DebugOut(L"[INFO] OVERLAPPING DAGGER ITEM");
		}
		else _objects->push_back(obj);
	}
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects)
{

	if (isJumping)
	{
		if (vy >= 0)
		{
			isCrouching = false;
			vy += SIMON_FALLING_SPEED * dt;
		}
		else
		{
			//if (this->rope->isActive())
				//isCrouching = false;
			vy += SIMON_JUMPING_FALLING_SPEED * dt;
		}

	}
	else {
		if (vy != 0)
		{
			vx = 0;
		}
		vy += SIMON_FALLING_SPEED * dt;
	}
	if (weapon != NULL) weapon->Update(dt);
	if (attack_timer.isActive()) {
		attack_timer.hasTicked();
	}
	vector<LPGAMEOBJECT> coObjects;
	OverLappingLogic(Objects,&coObjects);
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	//
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&coObjects, coEvents);

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

		bool should_x_change = true;
		bool should_y_change = true;
			
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
		}
		if (should_x_change) x += dx;
		if (should_y_change) y += dy;



		//
		
	}

	//

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	this->rope->Update(x,y,nx,dt, Objects);
	Focus();
	UpdateCurrentAnim();
}
void CSimon::Render() 
{
	if (fabulous_timer.isActive()&&!fabulous_timer.hasTicked()) {
		argb.fade();
	}
	else argb = CARGB();
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
	if (this->rope->isActive() || isUsingweapon || !isControllable || CTimeFreezer::GetInstance()->isActive()) return;
	switch (action) {
	case Action::ATTACK:
		if (!attack_timer.isActive())
		{
			attack_timer.Active();
			this->rope->Active();
			if (!isJumping)
			{			
				this->vx = 0;				
			}
			else isCrouching = false;
		}
		break;
	case Action::USE_WEAPON:
		heart--;
		isUsingweapon = true;
		weapon->Trigger();
		if (!isJumping)
		{
			this->vx = 0;
		}
		else isCrouching = false;
		break;
	}
	if (isJumping) return;
	//------------------------------
	switch (action) {
		case Action::JUMP:
			Jump();
			break;
		case Action::CROUCH:
			Crouch();
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

	if (this->rope->isActive()||isUsingweapon)
	{
		if (isCrouching) {
			currentAnim = nx > 0 ? (int)SimonAnimID::CROUCH_ATTACK_RIGHT : (int)SimonAnimID::CROUCH_ATTACK_LEFT;
		}
		else
		currentAnim = nx > 0 ? (int)SimonAnimID::ATTACK_RIGHT : (int)SimonAnimID::ATTACK_LEFT;
	}
	else if (isJumping)
	{
		if (isCrouching) {
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
		//if (isJumping) // fix later
			//y -= 10;
	}
}
void CSimon::Jump()
{
	//can't jump if simon is crouching or attacking or jumping 
	if (!isJumping&&!isCrouching && !isUsingweapon&&!this->rope->isActive())
	{
		isJumping = true;
		isCrouching = true;
		this->vy = -SIMON_JUMPING_SPEED;
		y += SIMON_IDLE_BBOX_HEIGHT - SIMON_CROUCHING_BBOX_HEIGHT;
	}
}
void CSimon::Crouch() {
	if (!isCrouching)
	{
		this->isCrouching = true;
		this->vx = 0;
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
void CSimon::FreezeAnimation()
{
	rope->FreezeAnimation();
	CGameObject::FreezeAnimation();
}
void CSimon::IncreaseRopeLevel()
{
	rope->IncreaseLevel();
}
void CSimon::ChangeWeapon(LPWEAPON weapon)
{
	delete this->weapon;
	this->weapon = weapon;

}
void CSimon::ForceIdle()
{
	StandUp();
	isUsingweapon = false;
	isJumping = false;
	if (vy < 0) vy = 1;
	rope->Deactive();
}