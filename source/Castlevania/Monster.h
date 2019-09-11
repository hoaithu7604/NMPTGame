#pragma once
#include "MoveableObject.h"
#include "Timer.h"
#define MONSTER_INVUL_DURATION 1000
class CMonster: public CMoveableObject
{
protected:
	int contactDamage;
	int point;
	CTimer invulTimer;
public:
	CMonster() :CMoveableObject() { invulTimer.SetTime(MONSTER_INVUL_DURATION); }
	CMonster(int point) :CMoveableObject() { this->point = point; invulTimer.SetTime(MONSTER_INVUL_DURATION); }
	virtual void TakeDamage(int damage);
	virtual void Destroy();
	virtual void GetReward();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};