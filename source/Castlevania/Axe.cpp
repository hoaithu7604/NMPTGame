#include "Axe.h"
#include "Simon.h"
void CAxe::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + WEAPON_AXE_BBOX_WIDTH;
	bottom = top + WEAPON_AXE_BBOX_HEIGHT;
}
CAxe::CAxe()
	:CWeapon()
{
	heartCost = WEAPON_AXE_HEARTCOST;
	damage = WEAPON_AXE_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_AXE_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_AXE_COOLDOWN);
	prevAnim = currentAnim = (int)AxeAnim::IDLE;
}
CAxe::CAxe(float x, float y)
	:CWeapon()
{
	heartCost = WEAPON_AXE_HEARTCOST;
	damage = WEAPON_AXE_DAMAGE;
	trigger_delay_timer.SetTime(WEAPON_AXE_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_AXE_COOLDOWN);
	prevAnim = currentAnim = (int)AxeAnim::IDLE;
	SetPosition(x, y);
}
void CAxe::Trigger()
{
	if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
	{
		cooldown_timer.Active();
		trigger_delay_timer.Active();
	}
}
void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (trigger_delay_timer.hasTicked())
	{
		//create projectile here
		float x, y;
		CSimon::GetInstance()->GetCentralPoint(x, y);
		int nx = CSimon::GetInstance()->GetDirection();
		CGameObject::AddObject(new CAxeProjectile(damage, x, y, nx));
		CSimon::GetInstance()->FinishUsingWeapon();
	}
}