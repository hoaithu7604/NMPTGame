#pragma once
#include "GameObject.h"
#define HEALTHICON_BBOX_WIDTH 9
#define HEALTHICON_BBOX_HEIGHT 15
enum class HealthIconAnim{
	PLAYER=700,
	ENEMY,
	EMPTY
};
class CHealthIcon :public CGameObject
{
public:
	CHealthIcon() { state = GAMEOBJECT_STATE_VISIBLE; }
};