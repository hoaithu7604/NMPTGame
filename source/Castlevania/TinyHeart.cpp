#include "TinyHeart.h"
#include "UnseenForce.h"
#include "Simon.h"
void CTinyHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + ITEM_TINYHEART_BBOX_WIDTH;
	bottom = top + ITEM_TINYHEART_BBOX_HEIGHT;
}
CTinyHeart::CTinyHeart(float x, float y)
	:CItemObject(ITEM_TINYHEART_POINT)
{
	currentAnim = (int)TinyHeartAnimID::IDLE;
	prevAnim = (int)TinyHeartAnimID::IDLE;
	this->x = x - ITEM_TINYHEART_BBOX_WIDTH / 2;
	this->y = y - ITEM_TINYHEART_BBOX_HEIGHT / 2;
}
void CTinyHeart::Render()
{
	if (isOnCamera()) CGameObject::Render();
}
void CTinyHeart::GetReward()
{
	CSimon::GetInstance()->AddHeart(ITEM_TINYHEART_HEART_VALUE);
	CItemObject::GetReward();
}
void CTinyHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	vy += dt * ITEM_TINYHEART_GRAVITY;

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
				else
				{
					y += dy;
				}
			}
		}
	}
	if (vy != 0)
	{
		vx += accelerationX * dt;
		if (abs(vx) > ITEM_TINYHEART_VELOCITY_X_MAX && vx * accelerationX > 0)
			accelerationX = -accelerationX;
	}
	else vy = 0.1f; // this is dumb, but whatever >.>
	if (!isOnCamera()) state = GAMEOBJECT_STATE_INVISIBLE;
}