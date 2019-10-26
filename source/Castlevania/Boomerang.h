#pragma once
#include "Weapon.h"
#include "BoomerangProjectile.h"
#define WEAPON_BOOMERANG_BBOX_WIDTH 28
#define WEAPON_BOOMERANG_BBOX_HEIGHT 28
#define WEAPON_BOOMERANG_COOLDOWN 1000
#define WEAPON_BOOMERANG_TRIGGER_DELAY 200 // delay time to create projectile
#define WEAPON_BOOMERANG_DAMAGE 1
#define WEAPON_BOOMERANG_HEARTCOST 1
enum class BoomerangAnim
{
	IDLE = 3300
};
class CBoomerang :public CWeapon
{
public:
	CBoomerang();
	CBoomerang(float x, float y);
	virtual void Trigger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};