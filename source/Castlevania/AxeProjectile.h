#pragma once
#include "MoveableObject.h"
#define AXE_PROJECTILE_BBOX_WIDTH 32
#define AXE_PROJECTILE_BBOX_HEIGHT 18
#define AXE_PROJECTILE_SPEED_X 0.25f
#define AXE_PROJECTILE_SPEED_Y 0.4f
#define WEAPON_AXE_PROJECTILE_SPAWN_POS_X 8
#define WEAPON_AXE_PROJECTILE_SPAWN_POS_Y -30
enum class AxeProjectileAnim {
	IDLE = 2801,

};
class CAxeProjectile : public CMoveableObject
{
	int ContactDamage;
public:
	CAxeProjectile(int damage, float x, float y, int nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};