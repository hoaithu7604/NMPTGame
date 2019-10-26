#include "BoomerangProjectile.h"
#include "Candle.h"
#include "Zombie.h"
void CBoomerangProjectile::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + BOOMERANG_PROJECTILE_BBOX_WIDTH;
	bottom = top + BOOMERANG_PROJECTILE_BBOX_HEIGHT;
}
void CBoomerangProjectile::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	if (!isOnCamera() || (forward == false && ((nx == DIRECTION_RIGHT && x > base_x) || (nx == DIRECTION_LEFT && x < base_x))))
		state = GAMEOBJECT_STATE_INVISIBLE;//remove when it goes off-screen
	else
	{
		if (abs(x - base_x) > BOOMERANG_PROJECTILE_MAX_DISTANCE&&forward == true)
		{
			if ((vx < 0 && nx == DIRECTION_RIGHT) || (vx > 0 && nx == DIRECTION_LEFT))
			{
				forward = false;
				nx = -nx;
				vx = -vx;
			}
			else
			{
				vx -= BOOMERANG_PROJECTILE_ACCEL * nx*dt;
			}
		}
		else vx += BOOMERANG_PROJECTILE_ACCEL * nx*dt;
		if (abs(vx) > BOOMERANG_PROJECTILE_MAX_SPEED) vx = nx*BOOMERANG_PROJECTILE_MAX_SPEED;

		this->dt = dt;
		dx = vx * dt;
		x += dx;



		for (int i = 0; i < coObjects->size(); i++)
		{
			if (isOverlapping(coObjects->at(i)))
			{
				if (dynamic_cast<CItemHolder*>(coObjects->at(i)) || dynamic_cast<CMonster*>(coObjects->at(i)))
				{
					coObjects->at(i)->TakeDamage(ContactDamage);

				}
			}
		}
		if (vx>0) currentAnim = (int)BoomerangProjectileAnim::RIGHT;
		else currentAnim = (int)BoomerangProjectileAnim::LEFT;
	}
}
void CBoomerangProjectile::Render() {
	//if (isOnCamera()) doesn't need it now since it will get removed anyway
	CGameObject::Render();
}
CBoomerangProjectile::CBoomerangProjectile(int damage, float x, float y, int nx)
	:CMoveableObject()
{
	ContactDamage = damage;
	//adjust x,y
	this->x = nx>0 ? (x + WEAPON_BOOMERANG_PROJECTILE_SPAWN_POS_X) : (x - WEAPON_BOOMERANG_PROJECTILE_SPAWN_POS_X - BOOMERANG_PROJECTILE_BBOX_WIDTH);
	this->y = y + WEAPON_BOOMERANG_PROJECTILE_SPAWN_POS_Y;
	this->base_x = this->x;
	this->nx = nx;
	this->forward = true;
	vx = BOOMERANG_PROJECTILE_MAX_SPEED * nx;
	vy = 0;
	prevAnim = currentAnim = (int)BoomerangProjectileAnim::RIGHT;
}
