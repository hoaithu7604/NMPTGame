#pragma once
#include "Weapon.h"
#define WEAPON_WATCH_BBOX_WIDTH 30
#define WEAPON_WATCH_BBOX_HEIGHT 32
#define WEAPON_WATCH_COOLDOWN 10000
#define WEAPON_WATCH_TRIGGER_DELAY 200 // delay time to trigger
#define WEAPON_WATCH_DURATION 5000
#define WEAPON_WATCH_HEARTCOST 5
enum class WatchAnim
{
	IDLE = 2600
};
class CWatch :public CWeapon
{
public:
	CWatch();
	CWatch(float x, float y);
	virtual void Trigger();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};