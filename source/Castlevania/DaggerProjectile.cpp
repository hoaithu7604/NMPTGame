#include "DaggerProjectile.h"

void CDaggerProjectile::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + DAGGER_PROJECTILE_BBOX_WIDTH;
	bottom = top + DAGGER_PROJECTILE_BBOX_HEIGHT;
}
void CDaggerProjectile::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	if (!isOnCamera())
		state = GAMEOBJECT_STATE_INVISIBLE;//remove when it goes off-screen
	else
	{

	}
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;
	
}
void CDaggerProjectile::Render() {
	//if (isOnCamera()) doesn't need it now since it will get removed anyway
		CGameObject::Render();
}
CDaggerProjectile::CDaggerProjectile(float x, float y, int nx)
	:CMoveableObject() 
{ 
	//adjust x,y
	this->x = nx>0?(x+WEAPON_DAGGER_PROJECTILE_SPAWN_POS_X):(x-WEAPON_DAGGER_PROJECTILE_SPAWN_POS_X-DAGGER_PROJECTILE_BBOX_WIDTH);
	this->y = y+ WEAPON_DAGGER_PROJECTILE_SPAWN_POS_Y;

	this->nx = nx;
	vx = DAGGER_PROJECTILE_SPEED*nx;
	prevAnim = currentAnim = nx>0?(int)DaggerProjectileAnim::RIGHT:(int)DaggerProjectileAnim::LEFT;
}
