#include "Fish.h"
#include "UnseenForce.h"
#include "Simon.h"
#include "FireBall.h"
#include "UnseenWater.h"
#include "BubbleEffect.h"
CFish::CFish(float x, float y, float vy)
	: CMonster(FISH_POINT, FISH_HEALTH_DEFAULT)
{
	SetPositionCentral(x, y);
	this->nx = nx;
	this->vy = vy;
	nx = 1;
//	vx = nx > 0 ? FISH_FLYING_SPEED_X : -FISH_FLYING_SPEED_X;
	currentAnim = prevAnim = nx > 0 ? (int)FishAnimID::IDLE_RIGHT : (int)FishAnimID::IDLE_LEFT;
	contactDamage = FISH_CONTACT_DAMAGE;
	shootingTimer.SetTime(SHOOTING_DELAY);
	shootingCooldownTimer.SetTime(SHOOTING_COOLDOWN);
}
void CFish::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + FISH_BBOX_WIDTH;
	bottom = top + FISH_BBOX_HEIGHT;
}
void CFish::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	
	// doing nothing while shooting
	if (!isShooting) 
	{
		//while not seeking for simon
		float x, y;
		CSimon::GetInstance()->GetPosition(x, y);
		if (x - this->x > 0)
			nx = DIRECTION_RIGHT;
		else nx = DIRECTION_LEFT;
		if (vy==0)
			vx = nx * FISH_WALKING_SPEED;
	}
	//check if it should shoot
	if (ShouldShoot()) Shoot();

	dx = vx * dt;
	dy = vy * dt;

	vy += WORLD_GRAVITY*dt;
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
		bool should_x_change = true;
		bool should_y_change = true;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CUnseenForce *>(e->obj))
			{
				if (e->ny < 0)
				{
					y += e->t * dy + ny * AVOID_OVERLAPPLING_FORCE;
					vy = 0;
					should_y_change = false;
				}
			}
			else if (dynamic_cast<CUnseenWater *>(e->obj))
			{
				float pos_x, pos_y;
				e->obj->GetPosition(pos_x, pos_y);
				pos_x = this->x + dx + FISH_BBOX_WIDTH / 2;
				CBubbleEffect::CreateEffect(pos_x, pos_y);
			}
		}
		if (should_x_change) x += dx;
		if (should_y_change) y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//update current anim
	if (isShooting)
		currentAnim = nx > 0 ? (int)FishAnimID::SHOOT_RIGHT:(int)FishAnimID::SHOOT_LEFT;
	else if (vx != 0)
		currentAnim = nx > 0 ? (int)FishAnimID::WALK_RIGHT : (int)FishAnimID::WALK_LEFT;
	else currentAnim = nx > 0 ? (int)FishAnimID::IDLE_RIGHT : (int)FishAnimID::IDLE_LEFT;


	if (isFarOffscreen()) state = GAMEOBJECT_STATE_INVISIBLE;
}
bool CFish::ShouldShoot()
{
	return (!shootingCooldownTimer.isActive() || shootingCooldownTimer.hasTicked()||isShooting);
}
void CFish::Shoot()
{
	if (!isShooting)
	{
		isShooting = true;
		shootingTimer.Active();
	}
	if (shootingTimer.hasTicked())
	{
		isShooting = false;
		float posX = nx > 0 ? x + FISH_BBOX_WIDTH : x;
		float posY = y + FIREBALL_SPAWN_Y;
		 
		CGameObject::AddObject(new CFireBall(posX, posY, nx));
		shootingCooldownTimer.Active();
	}
}