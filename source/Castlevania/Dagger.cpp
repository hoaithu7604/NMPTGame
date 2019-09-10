#include "Dagger.h"

void CDagger::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + WEAPON_DAGGER_BBOX_WIDTH;
	bottom = top + WEAPON_DAGGER_BBOX_HEIGHT;
}
CDagger::CDagger(float x, float y) 
	:CWeapon() 
{
	cooldown_timer.SetTime(WEAPON_DAGGER_COOLDOWN);
	prevAnim = currentAnim = (int)DaggerAnim::IDLE; 
	SetPosition(x, y);
}
