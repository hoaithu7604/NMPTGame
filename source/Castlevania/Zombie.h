#pragma once
#include "Monster.h"
#define ZOMBIE_POINT 100
#define ZOMBIE_BBOX_WIDTH 32
#define ZOMBIE_BBOX_HEIGHT 64
#define ZOMBIE_WALKING_SPEED 0.1f
enum class ZombieAnimID {
	LEFT=1300,
	RIGHT
};
class CZombie : public CMonster
{

public:
	CZombie();
	CZombie(float x, float y, float nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};