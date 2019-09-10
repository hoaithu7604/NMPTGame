#pragma once
#include "Weapon.h"
#define WEAPON_DAGGER_BBOX_WIDTH 32
#define WEAPON_DAGGER_BBOX_HEIGHT 18
#define WEAPON_DAGGER_COOLDOWN 5000
enum class DaggerAnim
{
	IDLE = 1000
};
class CDagger :public CWeapon
{
public:
	CDagger() :CWeapon() { cooldown_timer.SetTime(WEAPON_DAGGER_COOLDOWN); prevAnim = currentAnim = (int)DaggerAnim::IDLE; }
	CDagger(float x, float y);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};