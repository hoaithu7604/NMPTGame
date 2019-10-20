#include "BubbleEffect.h"

CBubbleEffect::CBubbleEffect(float x, float y)
	:CEffectObject(BUBBLE_EFFECT_LAST_TIME)
{
	currentAnim = (int)BubbleEffectAnim::IDLE;
	prevAnim = (int)BubbleEffectAnim::IDLE;
	this->x = x - BUBBLE_EFFECT_BBOX_WIDTH / 2;
	this->y = y - BUBBLE_EFFECT_BBOX_HEIGHT / 2;

	vx = BUBBLE_EFFECT_SPEED * rand() / RAND_MAX;
	vy = -sqrt(BUBBLE_EFFECT_SPEED*BUBBLE_EFFECT_SPEED - vx * vx);

	CGameObject::AddObject(this);
}

void CBubbleEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + BUBBLE_EFFECT_BBOX_WIDTH;
	bottom = top + BUBBLE_EFFECT_BBOX_HEIGHT;
};
void CBubbleEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	x += vx * dt;
	y += vy * dt;
	vy += BUBBLE_EFFECT_FALLING_SPEED * dt;
	if (timer.hasTicked())
	{
		state = GAMEOBJECT_STATE_INVISIBLE;
	}
}
void CBubbleEffect::CreateEffect(float x, float y)
{
	for (int i = 0; i < BUBBLE_EFFECT_COUNT; i++)
		CGameObject::AddObject(new CBubbleEffect(x, y));
}