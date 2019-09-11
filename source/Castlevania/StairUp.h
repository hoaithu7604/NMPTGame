#pragma once
#include "GameObject.h"
#define ABLE_TO_CLIMB_DISTANCE sqrt(16*16+32*32)
class CStairUp :public CGameObject
{
	float startX;
	float startY;
	float endX;
	float endY;
public:
	CStairUp(float x, float y, float width, float height);
	bool isAbleToClimb();
};