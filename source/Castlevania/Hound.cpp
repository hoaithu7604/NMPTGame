#include "Hound.h"
#include "Simon.h"
#include "UnseenForce.h"
CHound::CHound()
	:CMonster(HOUND_POINT, HOUND_HEALTH_DEFAULT)
{
	currentAnim = prevAnim = (int)HoundAnimID::IDLE_RIGHT;
	contactDamage = HOUND_CONTACT_DAMAGE;
}
CHound::CHound(float x, float y, float nx)
	: CMonster(HOUND_POINT, HOUND_HEALTH_DEFAULT)
{
	isJumping = false;
	this->x = x; this->y = y;
	this->nx = nx;
	currentAnim = prevAnim = nx > 0 ? (int)HoundAnimID::IDLE_RIGHT : (int)HoundAnimID::IDLE_RIGHT;
	contactDamage = HOUND_CONTACT_DAMAGE;
}
void CHound::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	if (vx == 0)
	{
		right = left + HOUND_BBOX_WIDTH;
		bottom = top + HOUND_BBOX_HEIGHT;
	}
	else {
		right = left + HOUND_RUNNING_BBOX_WIDTH;
		bottom = top + HOUND_RUNNING_BBOX_HEIGHT;
	}
}
void CHound::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (currentAnim == (int)HoundAnimID::IDLE_RIGHT || currentAnim == (int)HoundAnimID::IDLE_LEFT)
	{
		float x, y;
		CSimon::GetInstance()->GetCentralPoint(x, y);
		
		if (abs(this->x+HOUND_BBOX_WIDTH-x)<HOUND_JUMPSCARE_DISTANCE)
		{
			vx += nx*HOUND_RUNNING_SPEED;
			vy -= HOUND_JUMP_SPEED;
			isJumping = true;
		}
	}
	vy += dt * WORLD_GRAVITY;


	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
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
					if (isJumping)
					{
						isJumping = false;
						//change direction after finishing jumping
						nx = -nx;
						vx = -vx;
						//
					}
					vy = 0;
					should_y_change = false;
				}
			}
		}
		if (should_x_change)
			x += dx;
		if (should_y_change) y += dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//Update Anim
	if (isJumping)
	{
		currentAnim = nx > 0 ? (int)HoundAnimID::JUMP_RIGHT : (int)HoundAnimID::JUMP_LEFT;
	}
	else
	{
		if (vx==0)
			currentAnim = nx > 0 ? (int)HoundAnimID::IDLE_RIGHT : (int)HoundAnimID::IDLE_LEFT;
		else currentAnim = nx > 0 ? (int)HoundAnimID::RUN_RIGHT : (int)HoundAnimID::RUN_LEFT;
	}


	if (isFarOffscreen()) state = GAMEOBJECT_STATE_INVISIBLE;
}
