#pragma once
#include "Weapon.h"
#include "DaggerProjectile.h"
#define WEAPON_DAGGER_BBOX_WIDTH 32
#define WEAPON_DAGGER_BBOX_HEIGHT 18
#define WEAPON_DAGGER_COOLDOWN 1000
#define WEAPON_DAGGER_TRIGGER_DELAY 200 // delay time to create projectile
#define WEAPON_DAGGER_DAMAGE 1
enum class DaggerAnim
{
	IDLE = 1000
};
class CDagger :public CWeapon
{
public:
	CDagger();
	CDagger(float x, float y);
	virtual void Trigger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};