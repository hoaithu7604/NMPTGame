#include "Dagger.h"
#include "Simon.h"
void CDagger::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + WEAPON_DAGGER_BBOX_WIDTH;
	bottom = top + WEAPON_DAGGER_BBOX_HEIGHT;
}
CDagger::CDagger()
	:CWeapon()
{
	damage = WEAPON_DAGGER_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_DAGGER_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_DAGGER_COOLDOWN);
	prevAnim = currentAnim = (int)DaggerAnim::IDLE;
}
CDagger::CDagger(float x, float y) 
	:CWeapon() 
{
	damage = WEAPON_DAGGER_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_DAGGER_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_DAGGER_COOLDOWN);
	prevAnim = currentAnim = (int)DaggerAnim::IDLE; 
	SetPosition(x, y);
}
void CDagger::Trigger() 
{
	if (!cooldown_timer.isActive())
	{
		cooldown_timer.Active();
		trigger_delay_timer.Active();
	}
}
void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (trigger_delay_timer.hasTicked())
	{
		//create projectile here
		float x, y;
		CSimon::GetInstance()->GetCentralPoint(x, y);
		int nx = CSimon::GetInstance()->GetDirection();
		CGameObject::AddObject(new CDaggerProjectile(damage,x,y,nx));

		CSimon::GetInstance()->FinishUsingWeapon();
	}
	cooldown_timer.hasTicked(); //just to update timer;
}