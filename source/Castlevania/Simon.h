#pragma once
#include "MoveableObject.h"
#define SIMON_WALKING_SPEED 0.05f
#define SIMON_FALLING_SPEED 1
#define SIMON_JUMPING_SPEED 1


enum class SimonAnimID
{
	IDLE_RIGHT = 9900,
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
	static CSimon * __instance;
public:
	CSimon();
	void DoAction(Action action);
	void UpdateCurrentAnim();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();

	static CSimon * GetInstance();
};


