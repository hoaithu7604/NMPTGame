#pragma once
#include "GameObject.h"
#include "Timer.h"
#define WEAPON_HEART_COST_DEFAULT 1
class CWeapon : public CGameObject
{
protected:
	CTimer cooldown_timer;
	CTimer trigger_delay_timer;
	int damage;
	int heartCost= WEAPON_HEART_COST_DEFAULT;
public:
	CWeapon() :CGameObject() { state = GAMEOBJECT_STATE_NO_COLLISION; } // no collision for this class, only collsion for its projectile class
	bool isOnCooldown();
	int GetHeartCost() { return heartCost; }
	void SetCooldown(DWORD time) { cooldown_timer.SetTime(time); }
	virtual void Trigger() {};
};
typedef CWeapon*LPWEAPON;