#include "Monster.h"
#include "FlameEffect.h"
#include "CrossFlameEffect.h"
#include "OverlayBoard.h"
#include "UnseenForce.h"
void CMonster::Destroy()
{
	state = GAMEOBJECT_STATE_INVISIBLE;
	float x, y;
	GetCentralPoint(x, y);
	CGameObject::AddObject(new CFlameEffect(x, y));
	CGameObject::AddObject(new CCrossFlameEffect(x, y));
	GetReward();
}
void CMonster::GetReward()
{
	COverlayBoard::GetInstance()->IncreasePoint(point);
}
void CMonster::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
		if (should_x_change) x += dx;
		if (should_y_change) y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (isFarOffscreen()) state = GAMEOBJECT_STATE_INVISIBLE;// all monster despawn if they're far enought from camera view, override Update to avoid this
}
void CMonster::TakeDamage(int damage)
{
	OutputDebugString(L"CALLED FROM MONSTER");
	if (!invulTimer.isActive() || invulTimer.hasTicked())
	{
		health -= damage;
		if (health<=0)
		{
			health = 0;
			Destroy();
		}
		else invulTimer.Active();
	}
}
void CMonster::Render()
{
	if (isOnCamera()) {
		CGameObject::Render();
		RenderBoundingBox();
	}
}