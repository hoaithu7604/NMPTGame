#include "Boomerang.h"
#include "Simon.h"
void CBoomerang::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + WEAPON_BOOMERANG_BBOX_WIDTH;
	bottom = top + WEAPON_BOOMERANG_BBOX_HEIGHT;
}
CBoomerang::CBoomerang()
	:CWeapon()
{
	heartCost = WEAPON_BOOMERANG_HEARTCOST;
	damage = WEAPON_BOOMERANG_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_BOOMERANG_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_BOOMERANG_COOLDOWN);
	prevAnim = currentAnim = (int)BoomerangAnim::IDLE;
}
CBoomerang::CBoomerang(float x, float y)
	:CWeapon()
{
	heartCost = WEAPON_BOOMERANG_HEARTCOST;
	damage = WEAPON_BOOMERANG_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_BOOMERANG_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_BOOMERANG_COOLDOWN);
	prevAnim = currentAnim = (int)BoomerangAnim::IDLE;
	SetPosition(x, y);
}
void CBoomerang::Trigger()
{
	if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
	{
		cooldown_timer.Active();
		trigger_delay_timer.Active();
	}
}
void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (trigger_delay_timer.hasTicked())
	{
		//create projectile here
		float x, y;
		CSimon::GetInstance()->GetCentralPoint(x, y);
		int nx = CSimon::GetInstance()->GetDirection();
		CGameObject::AddObject(new CBoomerangProjectile(damage, x, y, nx));
		CSimon::GetInstance()->FinishUsingWeapon();
	}
}