#pragma once
#include "BigHeart.h"
#include "UnseenForce.h"
#include "Simon.h"
void CBigHeart::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + ITEM_BIGHEART_BBOX_WIDTH;
	bottom = top + ITEM_BIGHEART_BBOX_HEIGHT;
}
CBigHeart::CBigHeart(float x, float y) 
	:CItemObject(ITEM_BIGHEART_POINT)
{
	currentAnim = (int)BigHeartAnimID::IDLE;
	prevAnim = (int)BigHeartAnimID::IDLE;
	this->x = x-ITEM_BIGHEART_BBOX_WIDTH/2;
	this->y = y-ITEM_BIGHEART_BBOX_HEIGHT/2;
}
void CBigHeart::Render() 
{
	if (isOnCamera()) CGameObject::Render();
}
void CBigHeart::GetReward()
{
	CSimon::GetInstance()->AddHeart(ITEM_BIGHEART_HEART_VALUE);
	CItemObject::GetReward();
}