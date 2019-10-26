#pragma once
#include "MoveableObject.h"
#define BOOMERANG_PROJECTILE_BBOX_WIDTH 28
#define BOOMERANG_PROJECTILE_BBOX_HEIGHT 28
#define BOOMERANG_PROJECTILE_MAX_SPEED 0.25f
#define BOOMERANG_PROJECTILE_ACCEL 0.0004f
#define BOOMERANG_PROJECTILE_MAX_DISTANCE 150.f
#define WEAPON_BOOMERANG_PROJECTILE_SPAWN_POS_X 8
#define WEAPON_BOOMERANG_PROJECTILE_SPAWN_POS_Y -30
enum class BoomerangProjectileAnim {
	LEFT = 3301,
	RIGHT
};
class CBoomerangProjectile : public CMoveableObject
{
	int ContactDamage;
	bool forward = true;
	float base_x;
public:
	CBoomerangProjectile(int damage, float x, float y, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};