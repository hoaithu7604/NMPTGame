#include "DaggerProjectile.h"

void CDaggerProjectile::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + DAGGER_PROJECTILE_BBOX_WIDTH;
	bottom = top + DAGGER_PROJECTILE_BBOX_HEIGHT;
}
void CDaggerProjectile::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	if (isOnCamera())
		state = GAMEOBJECT_STATE_INVISIBLE;//remove when it goes off-screen
	else 
	{
		
	}
}
void CDaggerProjectile::Render() {
	//if (isOnCamera()) doesn't need it now since it will get removed anyway
		CGameObject::Render();
}
CDaggerProjectile::CDaggerProjectile(float x, float y, int nx)
	:CMoveableObject() 
{ 
	this->x = x;
	this->y = y;
	this->nx = nx;
	vx = DAGGER_PROJECTILE_SPEED*nx;
	prevAnim = currentAnim = (int)DaggerProjectileAnim::LEFT; 
}
