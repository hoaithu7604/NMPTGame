#include "BrickBreakingEffect.h"

CBrickBreakingEffect::CBrickBreakingEffect(float x, float y)
	:CEffectObject(BRICK_BREAKING_EFFECT_LAST_TIME)
{
	currentAnim = (int)BrickBreakingEffectAnim::IDLE;
	prevAnim = (int)BrickBreakingEffectAnim::IDLE;
	this->x = x - BRICK_BREAKING_EFFECT_BBOX_WIDTH / 2;
	this->y = y - BRICK_BREAKING_EFFECT_BBOX_HEIGHT / 2;

	vx = BRICK_BREAKING_EFFECT_SPEED * rand() / RAND_MAX - BRICK_BREAKING_EFFECT_SPEED/2;
	vy = -sqrt(BRICK_BREAKING_EFFECT_SPEED*BRICK_BREAKING_EFFECT_SPEED - vx * vx);

	CGameObject::AddObject(this);
}

void CBrickBreakingEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + BRICK_BREAKING_EFFECT_BBOX_WIDTH;
	bottom = top + BRICK_BREAKING_EFFECT_BBOX_HEIGHT;
};
void CBrickBreakingEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	x += vx * dt;
	y += vy * dt;
	vy += BRICK_BREAKING_EFFECT_FALLING_SPEED * dt;
	if (timer.hasTicked())
	{
		state = GAMEOBJECT_STATE_INVISIBLE;
	}
}