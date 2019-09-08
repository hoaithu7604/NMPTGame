#pragma once
#include "FlameEffect.h"

CFlameEffect::CFlameEffect(float x, float y)
	:CEffectObject(FLAME_EFFECT_LAST_TIME)
{
	currentAnim = (int)FlameEffectAnim::IDLE;
	prevAnim = (int)FlameEffectAnim::IDLE;
	this->x = x-FLAME_EFFECT_BBOX_WIDTH/2;
	this->y = y-FLAME_EFFECT_BBOX_HEIGHT/2;
	
	CGameObject::AddObject(this);
}
CFlameEffect::CFlameEffect()
	:CEffectObject(FLAME_EFFECT_LAST_TIME)
{ 
	currentAnim = (int)FlameEffectAnim::IDLE;
	prevAnim = (int)FlameEffectAnim::IDLE; 
	CGameObject::AddObject(this);
}
void CFlameEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + FLAME_EFFECT_BBOX_WIDTH;
	bottom = top + FLAME_EFFECT_BBOX_HEIGHT;
};