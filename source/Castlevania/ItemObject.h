#pragma once
#include "MoveableObject.h"
#define POINT_DEFAULT 0
class CItemObject :public CMoveableObject
{
protected:
	int point;
public:
	CItemObject():CMoveableObject(){ point = POINT_DEFAULT; state = GAMEOBJECT_STATE_ACTIVE; };
	CItemObject(int point):CMoveableObject(){ this->point = point; state = GAMEOBJECT_STATE_ACTIVE; };
	void SetPoint(int point) { this->point = point; }
	int GetPoint() { return point; }
	virtual void GetReward() { state = GAMEOBJECT_STATE_INVISIBLE; } //add point here later
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL); //all item should be affected by game gravity, except for somes
};