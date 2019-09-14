#pragma once
#include "Monster.h"
#define BAT_POINT 100
#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32
#define BAT_FLYING_SPEED_X 0.09f
#define BAT_FLYING_SPEED_Y 0.09f
#define BAT_HEALTH_DEFAULT 1
#define BAT_CONTACT_DAMAGE 1
#define BAT_ALPHA_Y 30
enum class BatAnimID {
	RIGHT = 2200,
	LEFT
};
class CBat : public CMonster
{
	float baseY;
public:
	CBat();
	CBat(float x, float y, float nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};