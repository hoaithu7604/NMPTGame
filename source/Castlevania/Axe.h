#pragma once
#include "Weapon.h"
#include "AxeProjectile.h"
#define WEAPON_AXE_BBOX_WIDTH 30
#define WEAPON_AXE_BBOX_HEIGHT 28
#define WEAPON_AXE_COOLDOWN 1000
#define WEAPON_AXE_TRIGGER_DELAY 200 // delay time to create projectile
#define WEAPON_AXE_DAMAGE 1
#define WEAPON_AXE_HEARTCOST 1
enum class AxeAnim
{
	IDLE = 2800
};
class CAxe :public CWeapon
{
public:
	CAxe();
	CAxe(float x, float y);
	virtual void Trigger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};