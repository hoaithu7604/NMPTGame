#include "FireBombFireEffect.h"
#include "Monster.h"
#include "ItemHolder.h"
void CFireBombFireEffect::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + FIREBOMB_EFFECT_BBOX_WIDTH;
	bottom = top + FIREBOMB_EFFECT_BBOX_HEIGHT;
}
CFireBombFireEffect::CFireBombFireEffect(float x, float y, int damage)
	:CEffectObject(FIREBOMB_EFFECT_DURATION)
{
	currentAnim = (int)FireBombFireEffectAnimID::IDLE;
	prevAnim = (int)FireBombFireEffectAnimID::IDLE;
	this->x = x - FIREBOMB_EFFECT_BBOX_WIDTH / 2;
	this->y = y - FIREBOMB_EFFECT_BBOX_HEIGHT; 
	this->damage = damage;
	CGameObject::AddObject(this);
}
void CFireBombFireEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (isOverlapping(coObjects->at(i)))
		{
			if (dynamic_cast<CItemHolder*>(coObjects->at(i)) || dynamic_cast<CMonster*>(coObjects->at(i)))
			{
				coObjects->at(i)->TakeDamage(damage);
			}
		}
	}
	if (timer.hasTicked())
	{
		state = GAMEOBJECT_STATE_INVISIBLE;
	}
}