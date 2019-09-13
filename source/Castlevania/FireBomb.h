#pragma once
#include "Weapon.h"
#define WEAPON_FIREBOMB_BBOX_WIDTH 26 //it's actually 32 but 26 looks nicer on item frame
#define WEAPON_FIREBOMB_BBOX_HEIGHT 32
#define WEAPON_FIREBOMB_COOLDOWN 1000
#define WEAPON_FIREBOMB_TRIGGER_DELAY 200 // delay time to create projectile
#define WEAPON_FIREBOMB_DAMAGE 1
#define WEAPON_FIREBOMB_HEARTCOST 1
enum class FireBombAnimID
{
	IDLE = 1900
};
class CFireBomb : public CWeapon
{
public:
	CFireBomb();
	CFireBomb(float x, float y);
	virtual void Trigger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};