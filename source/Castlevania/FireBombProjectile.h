#pragma once
#include "MoveableObject.h"
#define FIREBOMB_PROJECTILE_BBOX_WIDTH 16
#define FIREBOMB_PROJECTILE_BBOX_HEIGHT 16
#define WEAPON_FIREBOMB_PROJECTILE_SPAWN_POS_X 8
#define WEAPON_FIREBOMB_PROJECTILE_SPAWN_POS_Y -20
#define WEAPON_FIREBOMB_PROJECTILE_VELOCITY_X 0.15f
#define WEAPON_FIREBOMB_PROJECTILE_VELOCITY_Y 0.15f
#define WEAPON_FIREBOMB_FALLING_SPEED 0.0008f
#define WEAPON_FIREBOMB_FALLING_SPEED_MAX 0.4f
enum class FireBombProjectileAnim {
	RIGHT = 1901,
	LEFT
};
class CFireBombProjectile : public CMoveableObject
{
	int ContactDamage;
public:
	CFireBombProjectile(int damage, float x, float y, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};