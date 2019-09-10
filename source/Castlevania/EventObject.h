#pragma once
#include "GameObject.h"
class CEventObject:CGameObject
{
public:
	CEventObject() :CGameObject() { state = GAMEOBJECT_STATE_UPDATE_ONLY;}
};