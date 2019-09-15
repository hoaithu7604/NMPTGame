#include "Watch.h"
#include "Simon.h"
#include "TimeFreezer.h"
void CWatch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + WEAPON_WATCH_BBOX_WIDTH;
	bottom = top + WEAPON_WATCH_BBOX_HEIGHT;
}
CWatch::CWatch()
	:CWeapon()
{
	heartCost = WEAPON_WATCH_HEARTCOST;
	trigger_delay_timer.SetTime(WEAPON_WATCH_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_WATCH_COOLDOWN);
	prevAnim = currentAnim = (int)WatchAnim::IDLE;
}
CWatch::CWatch(float x, float y)
	:CWeapon()
{
	heartCost = WEAPON_WATCH_HEARTCOST;
	trigger_delay_timer.SetTime(WEAPON_WATCH_TRIGGER_DELAY);
	cooldown_timer.SetTime(WEAPON_WATCH_COOLDOWN);
	prevAnim = currentAnim = (int)WatchAnim::IDLE;
	SetPosition(x, y);
}
void CWatch::Trigger()
{
	if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
	{
		cooldown_timer.Active();
		trigger_delay_timer.Active();
	}
}
void CWatch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (trigger_delay_timer.hasTicked())
	{
		float x, y;
		CSimon::GetInstance()->GetCentralPoint(x, y);
		int nx = CSimon::GetInstance()->GetDirection();
		CSimon::GetInstance()->FinishUsingWeapon();
		//trigger time freezer here
		CTimeFreezer::GetInstance()->Active(WEAPON_WATCH_DURATION, false);
	}
}