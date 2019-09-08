#include "BigHeart.h"
#include "UnseenForce.h"
#include "Simon.h"
void CBigHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + ITEM_BIGHEART_BBOX_WIDTH;
	bottom = top + ITEM_BIGHEART_BBOX_HEIGHT;
}
CBigHeart::CBigHeart(float x, float y) 
	:CItemObject(ITEM_BIGHEART_POINT)
{
	currentAnim = (int)BigHeartAnimID::IDLE;
	prevAnim = (int)BigHeartAnimID::IDLE;
	this->x = x-ITEM_BIGHEART_BBOX_WIDTH/2;
	this->y = y-ITEM_BIGHEART_BBOX_HEIGHT/2;
}
void CBigHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
	vy += dt * WORLD_GRAVITY;
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
		//

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CUnseenForce *>(e->obj))
			{
				if (e->ny < 0)
				{
					y += e->t * dy + ny * AVOID_OVERLAPPLING_FORCE;
					vy = 0;
				}
				else y += dy;
			}
		}
	}
}
void CBigHeart::Render() 
{
	if (isOnCamera()) CGameObject::Render();
}
void CBigHeart::GetReward()
{
	CSimon::GetInstance()->AddHeart(ITEM_BIGHEART_HEART_VALUE);
	CItemObject::GetReward();
}