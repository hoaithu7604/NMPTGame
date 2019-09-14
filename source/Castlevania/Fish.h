#pragma once
#include "Monster.h"
#include "Timer.h"
#define FISH_POINT 100
#define FISH_BBOX_WIDTH 32
#define FISH_BBOX_HEIGHT 64
#define FISH_WALKING_SPEED 0.07f
#define FISH_HEALTH_DEFAULT 1
#define FISH_CONTACT_DAMAGE 1
#define SHOOTING_DELAY 1200
#define SHOOTING_COOLDOWN 10000
#define FIREBALL_SPAWN_Y 9
enum class FishAnimID {
	IDLE_RIGHT = 2300,
	IDLE_LEFT,
	WALK_RIGHT,
	WALK_LEFT,
	SHOOT_RIGHT,
	SHOOT_LEFT
};
class CFish : public CMonster
{
	bool isShooting;
	CTimer shootingTimer;
	CTimer shootingCooldownTimer;
public:
	CFish(float x, float y, float vy);
	bool ShouldShoot();
	void Shoot();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};