#pragma once
#include "FlameEffect.h"

CFlameEffect::CFlameEffect(float x, float y)
{
	currentAnim = (int)FlameEffectAnim::IDLE;
	prevAnim = (int)FlameEffectAnim::IDLE;
	this->x = x-FLAME_EFFECT_BBOX_WIDTH/2;
	this->y = y-FLAME_EFFECT_BBOX_HEIGHT/2;
	CEffectObject(FLAME_EFFECT_LAST_TIME);
	CGameObject::AddObject(this);
}
void CFlameEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + FLAME_EFFECT_BBOX_WIDTH;
	bottom = top + FLAME_EFFECT_BBOX_HEIGHT;
};