#pragma once
#include "EffectObject.h"


CEffectObject::CEffectObject() 
	:CGameObject() 
{ 
	state = GAMEOBJECT_STATE_NO_COLLISION;
	timer.SetTime(DEFAULT_LAST_TIME);
	timer.Active(); 
}
CEffectObject::CEffectObject(DWORD time) 
	: CGameObject() 
{
	state = GAMEOBJECT_STATE_NO_COLLISION;
	timer.SetTime(time); 
	timer.Active();
}

void CEffectObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (timer.hasTicked())
	{
		state = GAMEOBJECT_STATE_INVISIBLE;
	}
}
