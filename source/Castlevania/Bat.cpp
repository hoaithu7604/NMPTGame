#include "Bat.h"

CBat::CBat()
	:CMonster(BAT_POINT, BAT_HEALTH_DEFAULT)
{
	currentAnim = prevAnim = (int)BatAnimID::LEFT;
	contactDamage = BAT_CONTACT_DAMAGE;
}
CBat::CBat(float x, float y, float nx)
	: CMonster(BAT_POINT, BAT_HEALTH_DEFAULT)
{
	SetPositionCentral(x, y);
	this->baseY = y;
	this->nx = nx;
	vx = nx > 0 ? BAT_FLYING_SPEED_X : -BAT_FLYING_SPEED_X;
	vy = BAT_FLYING_SPEED_Y;
	currentAnim = prevAnim = nx > 0 ? (int)BatAnimID::RIGHT : (int)BatAnimID::LEFT;
	contactDamage = BAT_CONTACT_DAMAGE;
}
void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + BAT_BBOX_WIDTH;
	bottom = top + BAT_BBOX_HEIGHT;
}
void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	dx = vx * dt;
	dy = vy * dt;
	x += dx;
	y += dy;
	if (y > baseY + BAT_ALPHA_Y)
	{
		y = baseY + BAT_ALPHA_Y;
		vy = -vy;
	}
	if (y < baseY - BAT_ALPHA_Y)
	{
		y = baseY - BAT_ALPHA_Y;
		vy = -vy;
	}
	if (isFarOffscreen()) state = GAMEOBJECT_STATE_INVISIBLE;
}

