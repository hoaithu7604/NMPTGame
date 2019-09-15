#include "AxeProjectile.h"
#include "Candle.h"
#include "Zombie.h"
void CAxeProjectile::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + AXE_PROJECTILE_BBOX_WIDTH;
	bottom = top + AXE_PROJECTILE_BBOX_HEIGHT;
}
void CAxeProjectile::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	if (!isOnCamera())
		state = GAMEOBJECT_STATE_INVISIBLE;//remove when it goes off-screen
	else
	{
		this->dt = dt;
		dx = vx * dt;
		dy = vy * dt;
		vy += WORLD_GRAVITY * dt;
		x += dx;
		y += dy;
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
	}
}
void CAxeProjectile::Render() {
	//if (isOnCamera()) doesn't need it now since it will get removed anyway
	CGameObject::Render();
}
CAxeProjectile::CAxeProjectile(int damage, float x, float y, int nx)
	:CMoveableObject()
{
	ContactDamage = damage;
	//adjust x,y
	this->x = nx>0 ? (x + WEAPON_AXE_PROJECTILE_SPAWN_POS_X) : (x - WEAPON_AXE_PROJECTILE_SPAWN_POS_X - AXE_PROJECTILE_BBOX_WIDTH);
	this->y = y + WEAPON_AXE_PROJECTILE_SPAWN_POS_Y;

	this->nx = nx;
	vx = AXE_PROJECTILE_SPEED_X * nx;
	vy = -AXE_PROJECTILE_SPEED_Y;
	prevAnim = currentAnim = (int)AxeProjectileAnim::IDLE;
}
