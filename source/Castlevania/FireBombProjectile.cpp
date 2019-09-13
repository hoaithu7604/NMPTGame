#include "FireBombProjectile.h"
#include "Candle.h"
#include "Zombie.h"
#include "UnseenForce.h"
#include "FireBombFireEffect.h"
void CFireBombProjectile::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + FIREBOMB_PROJECTILE_BBOX_WIDTH;
	bottom = top + FIREBOMB_PROJECTILE_BBOX_HEIGHT;
}
void CFireBombProjectile::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	vy += WEAPON_FIREBOMB_FALLING_SPEED * dt;
	if (vy > WEAPON_FIREBOMB_FALLING_SPEED_MAX) vy = WEAPON_FIREBOMB_FALLING_SPEED_MAX;
	//overlapping
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
	//collsion
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		bool shouldExplore = false;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CUnseenForce *>(e->obj))
			{
				if (e->ny < 0)
				{
					y+= e->t * dy + e->ny * AVOID_OVERLAPPLING_FORCE;
					shouldExplore = true;
				}
				if (e->nx != 0)
				{
					x+= e->t * dx + e->nx * AVOID_OVERLAPPLING_FORCE;
					shouldExplore = true;
				}
			}
		}
		if (shouldExplore)
		{
			state = GAMEOBJECT_STATE_INVISIBLE;
			float pos_x = x + FIREBOMB_PROJECTILE_BBOX_WIDTH / 2;
			float pos_y = y + FIREBOMB_PROJECTILE_BBOX_HEIGHT;
			CFireBombFireEffect*effect = new CFireBombFireEffect(pos_x, pos_y, ContactDamage);
		}
		else
		{
			x += dx;
			y += dy;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	if (!isOnCamera())
		state = GAMEOBJECT_STATE_INVISIBLE;//remove when it goes off-screen
}
void CFireBombProjectile::Render() {
	//if (isOnCamera()) doesn't need it now since it will get removed anyway
	CGameObject::Render();
}
CFireBombProjectile::CFireBombProjectile(int damage, float x, float y, int nx)
	:CMoveableObject()
{
	ContactDamage = damage;
	//adjust x,y
	this->x = nx>0 ? (x + WEAPON_FIREBOMB_PROJECTILE_SPAWN_POS_X) : (x - WEAPON_FIREBOMB_PROJECTILE_SPAWN_POS_X - FIREBOMB_PROJECTILE_BBOX_WIDTH);
	this->y = y + WEAPON_FIREBOMB_PROJECTILE_SPAWN_POS_Y;
	this->nx = nx;
	vx = WEAPON_FIREBOMB_PROJECTILE_VELOCITY_X * nx;
	vy = -WEAPON_FIREBOMB_PROJECTILE_VELOCITY_Y; //flying up
	prevAnim = currentAnim = nx>0 ? (int)FireBombProjectileAnim::RIGHT : (int)FireBombProjectileAnim::LEFT;
	state = GAMEOBJECT_STATE_NO_COLLISION;
}
