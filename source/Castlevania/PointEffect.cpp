#pragma once
#include "PointEffect.h"
CPointEffect::CPointEffect(float x, float y, int point)
	:CEffectObject(POINT_EFFECT_LAST_TIME)
{
	currentAnim = (int)PointEffectAnim::p100;
	prevAnim = (int)PointEffectAnim::p100;
	this->x = x - POINT_EFFECT_BBOX_WIDTH / 2;
	this->y = y - POINT_EFFECT_BBOX_HEIGHT / 2;
	switch (point)
	{
	case 100: 
		currentAnim = (int)PointEffectAnim::p100;
		break;
	case 300:
		currentAnim = (int)PointEffectAnim::p300;
		break;
	case 700:
		currentAnim = (int)PointEffectAnim::p700;
		break;
	case 1000:
		currentAnim = (int)PointEffectAnim::p1000;
		break;
	}

	CGameObject::AddObject(this);
}
void CPointEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + POINT_EFFECT_BBOX_WIDTH;
	bottom = top + POINT_EFFECT_BBOX_HEIGHT;
};