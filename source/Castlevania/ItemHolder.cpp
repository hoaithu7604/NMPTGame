#include "ItemHolder.h"
#include "FlameEffect.h"
#include "BigHeart.h"
#include "RopeItem.h"
#include "DaggerItem.h"
#include "TinyHeart.h"
#include "MoneyBag.h"
void CItemHolder::Destroy() {
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float pos_x = (left + right) / 2;
	float pos_y = (top + bottom) / 2;
	CFlameEffect* effect = new CFlameEffect(pos_x,pos_y);
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
					CDaggerItem* daggeritem = new CDaggerItem(pos_x, pos_y);
					CGameObject::AddObject(daggeritem);
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
			}
		}
	
}