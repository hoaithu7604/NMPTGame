#pragma once
#include "CrossFlameEffect.h"

CCrossFlameEffect::CCrossFlameEffect(float x, float y)
	:CEffectObject(CROSSFLAME_EFFECT_LAST_TIME)
{
	currentAnim = (int)CrossFlameEffectAnim::IDLE;
	prevAnim = (int)CrossFlameEffectAnim::IDLE;
	//random point in radius of CROSSFLAME_SPAWNABLE_DISTANCE
	float xt, yt;
	float r = rand() * CROSSFLAME_SPAWNABLE_DISTANCE / RAND_MAX ;
	float alpha = 2.*rand() * acos(-1) / RAND_MAX;
	
	xt = r * cos(alpha);
	yt = r * sin(alpha);

	this->x = x+xt - CROSSFLAME_EFFECT_BBOX_WIDTH / 2;
	this->y = y+yt - CROSSFLAME_EFFECT_BBOX_HEIGHT / 2;

	CGameObject::AddObject(this);
}
CCrossFlameEffect::CCrossFlameEffect()
	:CEffectObject(CROSSFLAME_EFFECT_LAST_TIME)
{
	currentAnim = (int)CrossFlameEffectAnim::IDLE;
	prevAnim = (int)CrossFlameEffectAnim::IDLE;
	CGameObject::AddObject(this);
}
void CCrossFlameEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + CROSSFLAME_EFFECT_BBOX_WIDTH;
	bottom = top + CROSSFLAME_EFFECT_BBOX_HEIGHT;
};