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
#include "Zombie.h"
#include "Hound.h"
#include "ImBrick.h"
CSimon * CSimon::__instance = NULL;
CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}
CSimon::CSimon() 
	:CMoveableObject()
{
	//stats
	health = SIMON_HEALTH_DEFAULT;
	heart = SIMON_HEART_DEFAULT;
	weapon = NULL;
	rope = new CSimonRope();
	//flag
	isJumping = false;
	isCrouching = false;
	isUsingweapon = false;
	isControllable = true;
	isKnockingBack = false;
	isOnStairs = false;
	//timer
	fabulous_timer.SetTime(SIMON_FABULOUS_DURATION);
	attack_timer.SetTime(SIMON_ATTACK_COOLDOWN);
	forcedCrouchTimer.SetTime(SIMON_FORCED_CROUCH_DURATION);
	invulTimer.SetTime(SIMON_INVUL_TIMER);
	//others
	currentAnim = (int)SimonAnimID::IDLE_RIGHT;
	prevAnim = (int)SimonAnimID::IDLE_RIGHT;
	camera = CCamera::GetInstance();

	automover.SetSpeed(SIMON_WALKING_SPEED*.5f);
}
// no collision events to thing spawn on top of simon so let use this function
void CSimon::OverLappingLogic(vector<LPGAMEOBJECT>*objects,vector<LPGAMEOBJECT>*coObjects)
{
	if (!isOnStairs) stairs = NULL; 
	for (int i = 0; i < objects->size(); i++)
	{
		LPGAMEOBJECT obj= objects->at(i);
		if (dynamic_cast<CItemObject *>(obj)&&isOverlapping(obj))
		{			
			dynamic_cast<CItemObject*>(obj)->GetReward();
			DebugOut(L"[INFO] OVERLAPPING ITEM OBJECT");	
			if (dynamic_cast<CRopeItem*>(obj))
			{
				CTimeFreezer::GetInstance()->Active(SIMON_PICK_ITEM_FREEZE_TIME);
				fabulous_timer.Active();
				argb = RGB_RED;
			}
		}
		else if (dynamic_cast<CTorch *>(obj)&&isOverlapping(obj))
		{
			DebugOut(L"[INFO] OVERLAPPING TORCH");
		}
		else if (dynamic_cast<CFlameEffect*>(obj)&&isOverlapping(obj))
		{
			DebugOut(L"[INFO] OVERLAPPING FLAME EFFECT");
		}		
		else if (dynamic_cast<CMonster *>(obj)&&isOverlapping(obj))
		{
			OutputDebugString(L"TOUCHED MONSTER?!!??!?!?");
			if (TakingDamage(dynamic_cast<CMonster *>(obj)->GetContactDamage()))
			{
				float x, y;
				obj->GetCentralPoint(x, y);
				if (x > this->x)
				{
					KnockedBack(DIRECTION_LEFT);
				}
				else KnockedBack(DIRECTION_RIGHT);
			}
		}

		else if (dynamic_cast<CStairs*>(obj) && dynamic_cast<CStairs*>(obj)->isAbleToClimb())
		{
			stairs = dynamic_cast<CStairs*>(obj);
		}
		else coObjects->push_back(obj);
	}
}
void CSimon::CollisionLogic(DWORD dt, vector<LPGAMEOBJECT>*coObjects)
{
	this->dt = dt;
	automover.Update(dt); //ignore gravity when automover is actived by re-set vy
	dx = vx * dt;
	dy = vy * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
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

			if ((dynamic_cast<CUnseenForce *>(e->obj)||dynamic_cast<CImBrick *>(e->obj))&&!isOnStairs)
			{
				if (e->ny < 0)
				{
					should_y_change = false;
					if (isJumping)
					{
						isJumping = false;
						vx = 0;
					}
					if (isKnockingBack)
					{
						isKnockingBack = false;
						ForcedCrouch();
						vx = 0;
					}
					if (vy == SIMON_FALLING_SPEED_LIMIT) ForcedCrouch();
					vy = 0;
					y += e->t * dy + ny * AVOID_OVERLAPPLING_FORCE;
				}
				if (e->nx != 0)
				{
					x += e->t * dx + nx * AVOID_OVERLAPPLING_FORCE;
					should_x_change = false;
				}
			}
		}
		if (should_x_change) x += dx;
		if (should_y_change) y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//-----------------------------
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *Objects)
{
	if (!isOnStairs) //ignore normal gravity while on stairs
	{
		if (isJumping)
		{
			//jumping gravity
			if (vy >= 0)
			{
				isCrouching = false;
				vy += SIMON_JUMPING_FALLING_SPEED_ * dt;
			}
			else
				vy += SIMON_JUMPING_FALLING_SPEED * dt;
		}
		else {
			if (isKnockingBack)
			{
				//different falling speed while getting knocked back
				vy += SIMON_KNOCKED_FALLING_SPEED * dt;
			}
			else
			{
				//normal gravity
				if (vy != 0) vx = 0; //can't move while falling
				vy += SIMON_FALLING_SPEED * dt;
			}
		}
	}
	if (vy > SIMON_FALLING_SPEED_LIMIT) vy = SIMON_FALLING_SPEED_LIMIT;
	//update current weapon
	if (weapon != NULL) weapon->Update(dt);
	//update timer
	if (forcedCrouchTimer.hasTicked()) {
		ReleaseControl();
		StandUp();
	}
	//collision&overlapping event
	vector<LPGAMEOBJECT> coObjects; // for collidable objects
	OverLappingLogic(Objects,&coObjects);
	CollisionLogic(dt, &coObjects);

	UpdateCurrentAnim();
	this->rope->Update(x, y, nx, dt, Objects);
	Focus(); //focus camera, may change the way camera work later
}
void CSimon::Render() 
{
	if (fabulous_timer.isActive()) {
		if  (!fabulous_timer.hasTicked())
			argb.fade();
		else argb = CARGB();
	}
	if (invulTimer.isActive()) 
	{
		if (!invulTimer.hasTicked())
		{
			if (argb.alpha == 200)
				argb.alpha = 100;
			else if (argb.alpha == 100)
				argb.alpha = 200;
			else argb.alpha = 200;
		}
		else argb.alpha = 255;
	}
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
	if (this->rope->isActive() 
		||isKnockingBack||isUsingweapon||!isControllable
		||CTimeFreezer::GetInstance()->isActive()) return;

	switch (action) {
	case Action::ATTACK:
		if (!attack_timer.isActive()||attack_timer.hasTicked())
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
		heart = heart - weapon->GetHeartCost();
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
	if (vy == 0&&!isCrouching) {
		switch (action) {
		case Action::GO_DOWN_STAIRS:
			GoDownStairs();
			break;
		case Action::GO_UP_STAIRS:
			GoUpStairs();
			break;
		case Action::GO_STAIRS_LEFT:
			if (isOnStairs)
				if (stairs->GetStairsType() == STAIRS_TYPE_UP)
					GoDownStairs();
				else GoUpStairs();
				break;
		case Action::GO_STAIRS_RIGHT:
			if (isOnStairs)
				if (stairs->GetStairsType() == STAIRS_TYPE_UP)
					GoUpStairs();
				else GoDownStairs();
				break;
		}
	}
	
	if (isOnStairs) return;
	//------------------------------
	switch (action) {
		case Action::JUMP:
			Jump();
			break;
		case Action::CROUCH:
			if (stairs==NULL||stairs->ShouldCrouch()) Crouch(); // simon should not crouch in some cases when come in contact with stairs
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
	//if simon is not doing IDLE action, it try to deactive automover if it's actived and not forced mode
	if (action != Action::IDLE&&action!=Action::GO_DOWN_STAIRS&&action!=Action::GO_UP_STAIRS) automover.Deactive(); 
	
}
void CSimon::UpdateCurrentAnim() 
{
	if (this->rope->isActive()||isUsingweapon)
	{
		if (isCrouching) {
			currentAnim = nx > 0 ? (int)SimonAnimID::CROUCH_ATTACK_RIGHT : (int)SimonAnimID::CROUCH_ATTACK_LEFT;
		}
		else if (isOnStairs)
		{
			if (stairs->ShouldIdle(x, y, nx))
				currentAnim = nx > 0 ? (int)SimonAnimID::ATTACK_RIGHT : (int)SimonAnimID::ATTACK_LEFT;
			else
			{
				int stairstype = stairs->GetStairsType();
				if (stairstype == STAIRS_TYPE_UP)
					currentAnim = nx > 0 ? (int)SimonAnimID::UP_STAIR_ATTACK_RIGHT : (int)SimonAnimID::DOWN_STAIR_ATTACK_LEFT;
				else if (stairstype == STAIRS_TYPE_DOWN)
					currentAnim = nx > 0 ? (int)SimonAnimID::DOWN_STAIR_ATTACK_RIGHT : (int)SimonAnimID::UP_STAIR_ATTACK_LEFT;
			}
		}
		else
		currentAnim = nx > 0 ? (int)SimonAnimID::ATTACK_RIGHT : (int)SimonAnimID::ATTACK_LEFT;
	}
	else if (isOnStairs)
	{
		if (stairs->ShouldIdle(x,y,nx))
			currentAnim = nx > 0 ? (int)SimonAnimID::IDLE_RIGHT : (int)SimonAnimID::IDLE_LEFT;
		else
		{
			int stairstype = stairs->GetStairsType();
			if (stairstype == STAIRS_TYPE_UP)
			{
				if (vx == 0)
					currentAnim = nx > 0 ? (int)SimonAnimID::IDLE_UPSTAIRS_RIGHT : (int)SimonAnimID::IDLE_DOWNSTAIRS_LEFT;
				else
					currentAnim = nx > 0 ? (int)SimonAnimID::WALK_UPSTAIRS_RIGHT : (int)SimonAnimID::WALK_DOWNSTAIRS_LEFT;
			}
			else if (stairstype == STAIRS_TYPE_DOWN)
			{
				if (vx == 0)
					currentAnim = nx > 0 ? (int)SimonAnimID::IDLE_DOWNSTAIRS_RIGHT : (int)SimonAnimID::IDLE_UPSTAIRS_LEFT;
				else
					currentAnim = nx > 0 ? (int)SimonAnimID::WALK_DOWNSTAIRS_RIGHT : (int)SimonAnimID::WALK_UPSTAIRS_LEFT;
			}
		}
	}
	else if (isKnockingBack)
	{
		currentAnim = nx > 0 ? (int)SimonAnimID::DAMAGING_RIGHT : (int)SimonAnimID::DAMAGING_LEFT;
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
	if (!isJumping)
	{
		if (isCrouching)
		{
			isCrouching = false;
			y -= SIMON_IDLE_BBOX_HEIGHT - SIMON_CROUCHING_BBOX_HEIGHT;
		}
	}
	else isCrouching = false;
}
void CSimon::Jump()
{
	//can't jump if simon is crouching or attacking or jumping 
	if (vy==0&&!isJumping&&!isCrouching && !isUsingweapon&&!this->rope->isActive())
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
bool CSimon::TakingDamage(int damage)
{
	if (!invulTimer.isActive() || invulTimer.hasTicked())
	{
		invulTimer.Active();
		health -= damage;
		if (health <= 0) {
			health = 0;
			Die();
		}
		return true;
	}
	else return false; //taking damage failed
}
void CSimon::Die()
{
	// DEAD
}
void CSimon::KnockedBack(int Direction)
{
	if (isOnStairs) return;
	vy = -SIMON_KNOCKED_BACK_FORCE_Y;
	vx = Direction * SIMON_KNOCKED_BACK_FORCE_X;
	nx = -Direction;
	StandUp();
	isJumping = false;
	isUsingweapon = false;
	rope->Deactive();
	isKnockingBack = true;
	automover.Deactive(); // try to deactive automover if getting kb
}
void CSimon::ForcedCrouch()
{
	if (!forcedCrouchTimer.isActive() || forcedCrouchTimer.hasTicked())
	{
		Crouch();
		BlockControl();
		forcedCrouchTimer.Active();
	}
}
void CSimon::GoDownStairs()
{
	if (stairs != NULL) {
		stairs->Down();
	}
}
void CSimon::GoUpStairs()
{
	if (stairs != NULL) {
			stairs->Up();
	}
}
void CSimon::AutoMove(float x, float y,float v, int mode, int type)
{
	if (!automover.IsActive())
	{
		automover.SetSpeed(v);
		automover.SetTarget(x, y);
		automover.Active(mode, type);
	}
}
