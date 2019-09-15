#pragma once
#include "MoveableObject.h"
#include "Camera.h"
#define SIMON_WALKING_SPEED 0.15f
#define SIMON_FALLING_SPEED 0.012f 
#define SIMON_JUMPING_SPEED 0.4f // 
#define SIMON_JUMPING_FALLING_SPEED 0.0008f // gravity while jumping up
#define SIMON_JUMPING_FALLING_SPEED_ 0.01f //gravity while falling down after jumping up
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
#define SIMON_FALLING_SPEED_LIMIT 1.6f
#include "SimonRope.h"
#include "Timer.h"
#include "Dagger.h"
#include "TimeFreezer.h"
#include "AutoMover.h"
#include "Stairs.h"
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
	KNOCKED_BACK_RIGHT,
	KNOCKED_BACK_LEFT,
	WALK_DOWNSTAIRS_RIGHT,
	WALK_DOWNSTAIRS_LEFT,
	WALK_UPSTAIRS_RIGHT,
	WALK_UPSTAIRS_LEFT,
	IDLE_DOWNSTAIRS_RIGHT,
	IDLE_DOWNSTAIRS_LEFT,
	IDLE_UPSTAIRS_RIGHT,
	IDLE_UPSTAIRS_LEFT,
	ATTACK_CROUCH_RIGHT,
	ATTACK_CROUCH_LEFT,
	ATTACK_DOWNSTAIRS_RIGHT,
	ATTACK_DOWNSTAIRS_LEFT,
	ATTACK_UPSTAIRS_RIGHT,
	ATTACK_UPSTAIRS_LEFT,
	GO_IN,
	DIE_LEFT,
	DIE_RIGHT,
	DAMAGED_LEFT,
	DAMAGED_RIGHT
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
	bool isOnStairs;
	bool isInvul; //flag to check if simon is under effect of medicine jar
	//timer
	CTimer invulTimer;
	CTimer attack_timer; //attack cooldown timer
	CTimer fabulous_timer; // let simon stay fabulous while this timer is on lol
	CTimer forcedCrouchTimer; //use when simon falls at high speed or getting knocked back
	//others component
	CAutoMover automover;
	CStairs* stairs; //current stairs simon is overlapping
	
public:
	CSimon();
	//checking
	bool IsOnStairs() { return isOnStairs; }
	bool IsControllable() { return isControllable; }
	bool CanUseWeapon() { return weapon != NULL && !weapon->isOnCooldown() &&heart>=weapon->GetHeartCost(); }
	bool isMoveable() { return vy == 0 && !isJumping && !isUsingweapon && !isCrouching && !rope->isActive() && !CTimeFreezer::GetInstance()->isActive(); }
	void IncreaseRopeLevel();
	int GetHeart() { return heart; }
	void AddHeart(int heart) { this->heart += heart; }
	void AddHealth(int health) { this->health += health; if (this->health > SIMON_HEALTH_DEFAULT) this->health = SIMON_HEALTH_DEFAULT; }
	LPWEAPON GetWeapon() { return weapon; }
	void SetInvul(DWORD time) { isInvul = true; invulTimer.SetTime(time); invulTimer.Active(); }
	//action
	void SetOnStairs(bool b = true) { isOnStairs = b; }
	void GoUpStairs();
	void GoDownStairs();
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
	void AutoMove(float x, float y, float v=SIMON_WALKING_SPEED,int mode = AUTO_MOVER_MODE_DEFAULT, int type = AUTO_MOVER_TYPE_DEFAULT);
	//
	void UpdateCurrentAnim();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void FreezeAnimation();
	void OverLappingLogic(vector<LPGAMEOBJECT>*coObjects,vector<LPGAMEOBJECT>*_objects);
	void CollisionLogic(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
	static CSimon * GetInstance();
};



