#pragma once
#include "GameObject.h"
#include "Timer.h"
class CWeapon : public CGameObject
{
protected:
	CTimer cooldown_timer;
public:
	CWeapon() :CGameObject() { cooldown_timer.SetTime(1000); state = State(true, true, false); } // no collision for this class, only collsion for its projectile class
	bool isOnCooldown() { return cooldown_timer.isActive();} //simon->GetHeart() > 0 
	virtual void Trigger() {};
};
typedef CWeapon*LPWEAPON;