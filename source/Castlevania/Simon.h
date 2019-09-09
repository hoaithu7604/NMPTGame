#pragma once
#include "MoveableObject.h"
#include "Camera.h"
#define SIMON_WALKING_SPEED 0.2f
#define SIMON_FALLING_SPEED 0.012f
#define SIMON_JUMPING_SPEED 0.4f
#define SIMON_JUMPING_FALLING_SPEED 0.001f // lol ik my english sucks
#define SIMON_IDLE_BBOX_HEIGHT 64
#define SIMON_IDLE_BBOX_WIDTH 32
#define SIMON_CROUCHING_BBOX_HEIGHT 46
#define SIMON_ATTACK_COOLDOWN 600
#define SIMON_HEART_DEFAULT 5
#define SIMON_PICK_ITEM_FREEZE_TIME 1000
#define SIMON_FABULOUS_DURATION 1000
#define SIMON_HEALTH_DEFAULT 16
#include "SimonRope.h"
#include "Timer.h"
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
	LPSIMONROPE rope;
	CCamera * camera;
	static CSimon * __instance;
	bool isJumping;
	bool isCrouching;
	CTimer attack_timer;
	CTimer fabulous_timer; // let simon stay fabulous while this timer is on lol
	int heart;
public:
	CSimon();
	void DoAction(Action action);
	void UpdateCurrentAnim();
	void AddHeart(int heart) { this->heart += heart; }
	int GetHeart() { return heart; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void FreezeAnimation();
	void OverLappingLogic(vector<LPGAMEOBJECT>*coObjects,vector<LPGAMEOBJECT>*_objects);
	void StandUp();
	void Jump();
	void Focus();
	void IncreaseRopeLevel();
	static CSimon * GetInstance();
};



