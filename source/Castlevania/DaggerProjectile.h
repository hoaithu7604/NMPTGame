#pragma once
#include "MoveableObject.h"
#define DAGGER_PROJECTILE_BBOX_WIDTH 32
#define DAGGER_PROJECTILE_BBOX_HEIGHT 18
#define DAGGER_PROJECTILE_SPEED 0.8f
#define WEAPON_DAGGER_PROJECTILE_SPAWN_POS_X 8
#define WEAPON_DAGGER_PROJECTILE_SPAWN_POS_Y -20
enum class DaggerProjectileAnim {
	RIGHT=1000,
	LEFT
};
class CDaggerProjectile : public CMoveableObject
{
	int ContactDamage;
public:
	CDaggerProjectile() :CMoveableObject() { vx = DAGGER_PROJECTILE_SPEED; prevAnim = currentAnim = (int)DaggerProjectileAnim::LEFT; }
	CDaggerProjectile(float x, float y, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};