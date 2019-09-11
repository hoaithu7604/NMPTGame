#pragma once
#include "MoveableObject.h"
#include "Camera.h"
#define SIMON_WALKING_SPEED 0.15f
#define SIMON_FALLING_SPEED 0.012f
#define SIMON_JUMPING_SPEED 0.4f
#define SIMON_JUMPING_FALLING_SPEED 0.0008f // lol ik my english sucks
#define SIMON_IDLE_BBOX_HEIGHT 64
#define SIMON_IDLE_BBOX_WIDTH 32
#define SIMON_CROUCHING_BBOX_HEIGHT 46
#define SIMON_ATTACK_COOLDOWN 600
#define SIMON_HEART_DEFAULT 5
#define SIMON_PICK_ITEM_FREEZE_TIME 500
#define SIMON_FABULOUS_DURATION 500
#define SIMON_HEALTH_DEFAULT 16
#define SIMON_INVUL_TIMER 3000
#define SIMON_KNOCKED_BACK_FORCE_X 0.1f
#define SIMON_KNOCKED_BACK_FORCE_Y 0.2f
#define SIMON_KNOCKED_FALLING_SPEED 0.0008f //apply different gravity while being knocked back
#define SIMON_FORCED_CROUCH_DURATION 300
#include "SimonRope.h"
#include "Timer.h"
#include "Dagger.h"
#include "TimeFreezer.h"
enum class SimonAnimID
{
	IDLE_RIGHT = 100,
	IDLE_LEFT,
	WALK_RIGHT,
	WALK_LEFT,
	CROUCH_RIGHT,
	CROUCH_LEFT,
	ATTACK_RIGHT,
	ATTACK_LEFT,
	PUSHED_BACK_RIGHT,
	PUSHED_BACK_LEFT,
	WALK_DOWNSTAIRS_RIGHT,
	WALK_DOWNSTAIRS_LEFT,
	WALK_UPSTAIRS_RIGHT,
	WALK_UPSTAIRS_LEFT,
	IDLE_DOWNSTAIRS_RIGHT,
	IDLE_DOWNSTAIRS_LEFT,
	IDLE_UPSTAIRS_RIGHT,
	IDLE_UPSTAIRS_LEFT,
	CROUCH_ATTACK_RIGHT,
	CROUCH_ATTACK_LEFT,
	DOWN_STAIR_ATTACK_RIGHT,
	DOWN_STAIR_ATTACK_LEFT,
	UP_STAIR_ATTACK_RIGHT,
	UP_STAIR_ATTACK_LEFT,
	GO_IN,
	DIE_LEFT,
	DIE_RIGHT,
	DAMAGING_LEFT,
	DAMAGING_RIGHT
};

class CSimon : public CMoveableObject
{
	CCamera * camera;
	static CSimon * __instance;
	//stats
	int heart;
	LPSIMONROPE rope;
	LPWEAPON weapon;
	//flag
	bool isControllable;
	bool isJumping;
	bool isCrouching;
	bool isUsingweapon;
	bool isKnockingBack;
	//timer
	CTimer invulTimer;
	CTimer attack_timer; //attack cooldown timer
	CTimer fabulous_timer; // let simon stay fabulous while this timer is on lol
	CTimer forcedCrouchTimer; //use when simon falls at high speed or getting knocked back
public:
	CSimon();
	bool CanUseWeapon() { return weapon != NULL && heart > 0 && !weapon->isOnCooldown(); }
	bool isMoveable() { return vy == 0 && !isJumping && !isUsingweapon && !isCrouching && !rope->isActive() && !CTimeFreezer::GetInstance()->isActive(); }
	void IncreaseRopeLevel();
	int GetHeart() { return heart; }
	void AddHeart(int heart) { this->heart += heart; }
	LPWEAPON GetWeapon() { return weapon; }

	void ForcedCrouch();
	void StandUp();
	void Jump();
	void Crouch();
	void ForceIdle();
	void BlockControl() { isControllable=false; }
	void ReleaseControl() { isControllable = true; }
	void FinishUsingWeapon() { isUsingweapon = false; }
	void ChangeWeapon(LPWEAPON weapon);
	void DoAction(Action action);
	void Focus();
	bool TakingDamage(int damage);
	void Die();
	void KnockedBack(int direction);
	
	void UpdateCurrentAnim();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void FreezeAnimation();
	void OverLappingLogic(vector<LPGAMEOBJECT>*coObjects,vector<LPGAMEOBJECT>*_objects);
		
	static CSimon * GetInstance();
};



