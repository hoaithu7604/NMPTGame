#pragma once
#include "GameObject.h"
#include "Timer.h"
class CWeapon : public CGameObject
{
protected:
	CTimer cooldown_timer;
	CTimer trigger_delay_timer;
	int damage;
public:
	CWeapon() :CGameObject() { state = GAMEOBJECT_STATE_NO_COLLISION; } // no collision for this class, only collsion for its projectile class
	bool isOnCooldown() { return cooldown_timer.isActive()&&!cooldown_timer.hasTicked();} //simon->GetHeart() > 0 
	virtual void Trigger() {};
};
typedef CWeapon*LPWEAPON;