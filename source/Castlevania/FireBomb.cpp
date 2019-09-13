#include "FireBomb.h"
#include "Simon.h"
#include "FireBombProjectile.h"
void CFireBomb::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + WEAPON_FIREBOMB_BBOX_WIDTH;
	bottom = top + WEAPON_FIREBOMB_BBOX_HEIGHT;
}
CFireBomb::CFireBomb()
	:CWeapon()
{
	heartCost = WEAPON_FIREBOMB_HEARTCOST;
	damage = WEAPON_FIREBOMB_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_FIREBOMB_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_FIREBOMB_COOLDOWN);
	prevAnim = currentAnim = (int)FireBombAnimID::IDLE;
}
CFireBomb::CFireBomb(float x, float y)
	:CWeapon()
{
	heartCost = WEAPON_FIREBOMB_HEARTCOST;
	damage = WEAPON_FIREBOMB_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_FIREBOMB_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_FIREBOMB_COOLDOWN);
	prevAnim = currentAnim = (int)FireBombAnimID::IDLE;
	SetPosition(x, y);
}
void CFireBomb::Trigger()
{
	if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
	{
		cooldown_timer.Active();
		trigger_delay_timer.Active();
	}
}
void CFireBomb::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (trigger_delay_timer.hasTicked())
	{
		//create projectile here
		float x, y;
		CSimon::GetInstance()->GetCentralPoint(x, y);
		int nx = CSimon::GetInstance()->GetDirection();
		CGameObject::AddObject(new CFireBombProjectile(damage, x, y, nx));
		CSimon::GetInstance()->FinishUsingWeapon();
	}
}