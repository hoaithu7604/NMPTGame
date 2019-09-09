#pragma once
#include "GameObject.h"
#define HEALTHICON_BBOX_WIDTH 8
#define HEALTHICON_BBOX_HEIGHT 14
enum class HealthIconAnim{
	PLAYER=700,
	ENEMY,
	EMPTY
};
class CHealthIcon :public CGameObject
{
public:
	CHealthIcon() { prevAnim = currentAnim = (int)HealthIconAnim::PLAYER; state = GAMEOBJECT_STATE_VISIBLE; }
};