#include "FireBall.h"
#include "CrossFlameEffect.h"
#include "FlameEffect.h"
CFireBall::CFireBall(float x, float y,float nx)
	:CEffectObject(FIREBALL_LAST_TIME)
{
	health = FIREBALL_HEALTH;
	state = GAMEOBJECT_STATE_ACTIVE;
	this->x = x - FIREBALL_BBOX_WIDTH / 2;
	this->y = y - FIREBALL_BBOX_HEIGHT / 2;
	this->nx = nx;
	vx = nx * FIREBALL_SPEED;
	prevAnim = currentAnim = nx > 0 ? (int)FireBallAnim::RIGHT : (int)FireBallAnim::LEFT;
	CGameObject::AddObject(this);
}

void CFireBall::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
};
void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	x += vx * dt;
	if (!isOnCamera())
		state = GAMEOBJECT_STATE_INVISIBLE;
}
void CFireBall::Destroy()
{
	state = GAMEOBJECT_STATE_INVISIBLE;
	float x, y;
	GetCentralPoint(x, y);
	CGameObject::AddObject(new CFlameEffect(x, y));
	CGameObject::AddObject(new CCrossFlameEffect(x, y));
}