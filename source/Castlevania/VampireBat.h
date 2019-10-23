#pragma once
#include "Monster.h"
#include "Timer.h"
#define VAMPIREBAT_POINT 1000
#define VAMPIREBAT_BBOX_WIDTH 96
#define VAMPIREBAT_BBOX_HEIGHT 44
#define VAMPIREBAT_HEALTH_DEFAULT 16
#define VAMPIREBAT_CONTACT_DAMAGE 2
#define VAMPIREBAT_ATTACK_COOLDOWN 4000
#define VAMPIREBAT_ATTACK_DELAY 500
#define VAMPIREBAT_ACCEL 0.0004f // .0001f
#define VAMPIREBAT_VELOCITY_MAX 0.45f
#define VAMPIREBAT_HOVER_DISTANCE 200
#define VAMPIREBAT_ALPHA_Y 70
#define VAMPIREBAT_SPEED_X 0.15f
#define VAMPIREBAT_SPEED_Y 0.15f
#define VAMPIREBAT_FLAME_X 15.f
#define VAMPIREBAT_FLAME_Y 15.f
enum class VampireBatAnimID {
	SLEEP = 3000,
	FLY
};
class CVampireBat : public CMonster
{
	bool isAttacking;
	float targetX;
	float targetY;
	bool isSleeping;
	CTimer attackCDTimer;
	CTimer attackDLTimer;
	CGameObject* effect;
	int rd;
public:
	void Wake() { isSleeping = false; }
	CVampireBat(float x, float y);
	virtual void Render() { if (isAlmostOnCamera()) CGameObject::Render(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};