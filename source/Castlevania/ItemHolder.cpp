#pragma once
#include "ItemHolder.h"
#include "FlameEffect.h"
#include "BigHeart.h"
#include "RopeItem.h"
#include "DaggerItem.h"
#include "TinyHeart.h"
#include "MoneyBag.h"
#include "FireBombItem.h"
#include "Cross.h"
#include "PorkChop.h"
#include "WatchItem.h"
#include "CrossFlameEffect.h"
#include "MedicineJar.h"
#include "AxeItem.h"
#include "Nirensya.h"
#include "BoomerangItem.h"
void CItemHolder::Destroy() {
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float pos_x = (left + right) / 2;
	float pos_y = (top + bottom) / 2;
	CFlameEffect* effect = new CFlameEffect(pos_x,pos_y);
	CGameObject::AddObject(new CCrossFlameEffect(pos_x, pos_y));
	delay_timer.Active();
	state = GAMEOBJECT_STATE_UPDATE_ONLY;
}

void CItemHolder::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
		if (delay_timer.hasTicked())
		{
			state = GAMEOBJECT_STATE_INVISIBLE;
			float left, top, right, bottom;
			GetBoundingBox(left, top, right, bottom);
			float pos_x = (left + right) / 2;
			float pos_y = (top + bottom) / 2;
			//spawn item here 
			for (int i = 0; i < item.size(); i++) {
				if (item[i] == ITEMCODE_BIGHEART)
				{
					CBigHeart* bigheart = new CBigHeart(pos_x, pos_y);
					CGameObject::AddObject(bigheart);
				}
				else if (item[i] == ITEMCODE_ROPEITEM)
				{
					CRopeItem* ropeitem = new CRopeItem(pos_x, pos_y);
					CGameObject::AddObject(ropeitem);
				}
				else if (item[i] == ITEMCODE_DAGGERITEM)
				{
					CDaggerItem* firebombitem = new CDaggerItem(pos_x, pos_y);
					CGameObject::AddObject(firebombitem);
				}
				else if (item[i] == ITEMCODE_TINYHEART)
				{
					CTinyHeart* tinyheart = new CTinyHeart(pos_x, pos_y);
					CGameObject::AddObject(tinyheart);
				}
				else if (item[i] == ITEMCODE_MONEYBAG1)
				{
					CMoneyBag* moneybag = new CMoneyBag(pos_x, pos_y, MONEYBAG_TIER_ONE);
					CGameObject::AddObject(moneybag);
				}
				else if (item[i] == ITEMCODE_MONEYBAG2)
				{
					CMoneyBag* moneybag = new CMoneyBag(pos_x, pos_y, MONEYBAG_TIER_TWO);
					CGameObject::AddObject(moneybag);
				}
				else if (item[i] == ITEMCODE_MONEYBAG3)
				{
					CMoneyBag* moneybag = new CMoneyBag(pos_x, pos_y, MONEYBAG_TIER_THREE);
					CGameObject::AddObject(moneybag);
				}
				else if (item[i] == ITEMCODE_MONEYBAG4)
				{
					CMoneyBag* moneybag = new CMoneyBag(pos_x, pos_y, MONEYBAG_TIER_FOUR);
					CGameObject::AddObject(moneybag);
				}
				else if (item[i] == ITEMCODE_FIREBOMBITEM)
				{
					CFireBombItem* firebombitem = new CFireBombItem(pos_x, pos_y);
					CGameObject::AddObject(firebombitem);
				}
				else if (item[i] == ITEMCODE_CROSS)
				{
					CCross* cross = new CCross(pos_x, pos_y);
					CGameObject::AddObject(cross);
				}
				else if (item[i] == ITEMCODE_PORKCHOP)
				{
					CPorkChop* porkchop = new CPorkChop(pos_x, pos_y);
					CGameObject::AddObject(porkchop);
				}
				else if (item[i] == ITEMCODE_WATCHITEM)
				{
					CWatchItem* watchitem = new CWatchItem(pos_x, pos_y);
					CGameObject::AddObject(watchitem);
				}
				else if (item[i] == ITEMCODE_MEDICINEJAR)
				{
					CMedicineJar* mj = new CMedicineJar(pos_x, pos_y);
					CGameObject::AddObject(mj);
				}
				else if (item[i] == ITEMCODE_AXEITEM)
				{
					CAxeItem* axe = new CAxeItem(pos_x,pos_y);
					CGameObject::AddObject(axe);
				}
				else if (item[i] == ITEMCODE_NIRENSYA)
				{
					CNirensya* nirensya = new CNirensya(pos_x, pos_y);
					CGameObject::AddObject(nirensya);
				}
				else if (item[i] == ITEMCODE_BOOMERANG)
				{
					CBoomerangItem* bmr = new CBoomerangItem(pos_x, pos_y);
					CGameObject::AddObject(bmr);
				}
			}
		}
	
}