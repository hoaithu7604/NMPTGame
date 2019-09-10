#include "ItemHolder.h"
#include "FlameEffect.h"
#include "BigHeart.h"
#include "RopeItem.h"
#include "DaggerItem.h"
void CItemHolder::Destroy() {
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float pos_x = (left + right) / 2;
	float pos_y = (top + bottom) / 2;
	CFlameEffect* effect = new CFlameEffect(pos_x,pos_y);

	delay_timer.Active();
	currentAnim = -1; // stop it to be rendered, but still be updated
}

void CItemHolder::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (delay_timer.isActive())
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
			}
		}
	}
}