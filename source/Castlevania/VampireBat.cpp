#include "VampireBat.h"
#include "Simon.h"
#include "CrossFlameEffect.h"
CVampireBat::CVampireBat(float x, float y)
	: CMonster(VAMPIREBAT_POINT, VAMPIREBAT_HEALTH_DEFAULT)
{
	SetPosition(x, y);
	isSleeping = true;
	isAttacking = false;
	currentAnim = prevAnim = (int)VampireBatAnimID::SLEEP;
	contactDamage = VAMPIREBAT_CONTACT_DAMAGE;
	attackCDTimer.SetTime(VAMPIREBAT_ATTACK_COOLDOWN);
	attackDLTimer.SetTime(VAMPIREBAT_ATTACK_DELAY);
}
void CVampireBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + VAMPIREBAT_BBOX_WIDTH;
	bottom = top + VAMPIREBAT_BBOX_HEIGHT;
}
void CVampireBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (!isSleeping)
	{
		//seek for simon when ready to attack
		if (!attackCDTimer.isActive() || attackCDTimer.hasTicked())
		{
			CSimon::GetInstance()->GetCentralPoint(targetX, targetY);
			//re-locate target point
			targetX -= VAMPIREBAT_BBOX_WIDTH / 2;
			targetY -= VAMPIREBAT_BBOX_HEIGHT / 2;
			attackCDTimer.Active();
			attackDLTimer.Active();
		}
		if (attackDLTimer.hasTicked())
		{
			isAttacking = true;
		}
		if (isAttacking)
		{
			float distance = sqrt((x - targetX)*(x - targetX) + (y - targetY)*(y - targetY));
			float v = sqrt(vx*vx + vy * vy);
			float t = dt*v / distance;
			if (t < 1)
			{
				//have not reached
				float targetV;
				if (v + VAMPIREBAT_ACCEL * dt > VAMPIREBAT_VELOCITY_MAX)
					targetV = VAMPIREBAT_VELOCITY_MAX;
				else
					targetV = v + VAMPIREBAT_ACCEL * dt;
				vx = (targetV)/distance*(targetX-x);
				vy = (targetV)/distance*(targetY-y);
			}
			else
			{
				vx = 0;
				vy = 0;
				isAttacking = false;
			}
		}
		if (!isAttacking&&attackCDTimer.isActive() && !attackCDTimer.hasTicked())
		{
			CSimon::GetInstance()->GetCentralPoint(targetX, targetY);
			//re-locate target point
			targetX -= VAMPIREBAT_BBOX_WIDTH / 2;
			targetY -= VAMPIREBAT_BBOX_HEIGHT / 2;
			float distance = sqrt((x - targetX)*(x - targetX) + (y - targetY)*(y - targetY));
			if (distance > VAMPIREBAT_HOVER_DISTANCE)
			{
				//try to approach target if too far
				float t = VAMPIREBAT_SPEED_X / distance;
				vx = (targetX - x)*t;
				vy = (targetY - y)*t;
			}
			else
			{
				vx = 0;
				if (y > targetY - VAMPIREBAT_ALPHA_Y)
				{
					//try to stay higher than target
					vy = -VAMPIREBAT_SPEED_Y;
				}
				else vy = 0;
			}
		}
		

		float left, top, right, bottom;
		//keep him inside playing arena
		CCamera::GetInstance()->GetViewSize(top, left, bottom,right);
		if (x < left) vx = abs(vx);
		if (x + VAMPIREBAT_BBOX_WIDTH > right) vx = -abs(vx);
		if (y < top) vy = abs(vy);
		if (y + VAMPIREBAT_BBOX_HEIGHT > bottom) vy = -abs(vy);
		dx = vx * dt;
		dy = vy * dt;
		x += dx;
		y += dy;

		if (invulTimer.isActive() && !invulTimer.hasTicked())
		{
			float pos_x = x;
			if (rd == 0)
				pos_x += (VAMPIREBAT_BBOX_WIDTH / 2 - VAMPIREBAT_FLAME_X);
			else
				pos_x += (VAMPIREBAT_BBOX_WIDTH / 2 + VAMPIREBAT_FLAME_X);
			float pos_y = y + VAMPIREBAT_FLAME_Y;
			if (effect == NULL||effect->GetState()==GAMEOBJECT_STATE_INVISIBLE)
			{
				rd = rand() % 2;
				effect = new CCrossFlameEffect(pos_x, pos_y);
				CGameObject::AddObject(effect);
			}
			else effect->SetPosition(pos_x, pos_y);
		}
	}

	// update animation
	currentAnim = isSleeping ? (int)VampireBatAnimID::SLEEP : (int)VampireBatAnimID::FLY;
}
