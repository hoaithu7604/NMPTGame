#pragma once
#include "ItemObject.h"
#include "UnseenForce.h"
void CItemObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
		}
		if (should_y_change) y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (!isOnCamera()) state = GAMEOBJECT_STATE_INVISIBLE; // all items should despawn when it's offscreen
}
void CItemObject::Render()
{
	if (isOnCamera()) CGameObject::Render(); // all items should only be rendered if it's onscreen
}