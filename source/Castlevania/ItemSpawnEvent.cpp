#include "ItemSpawnEvent.h"
#include "Simon.h"
#include "MoneyBag.h"
bool CItemSpawnEvent::ShouldTrigger()
{
	return !isTriggered && isContaining(CSimon::GetInstance());
}
void CItemSpawnEvent::Trigger()
{
	CGameObject::AddObject(new CMoneyBag(targetX, targetY, MONEYBAG_TIER_FOUR));// just spawn moneybag4 for now :/
	isTriggered = true;
}