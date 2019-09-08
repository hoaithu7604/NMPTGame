#include "ItemHolder.h"
#include "FlameEffect.h"
#include "BigHeart.h"

void CItemHolder::Destroy() {
	state = GAMEOBJECT_STATE_INVISIBLE;
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float pos_x = (left + right) / 2;
	float pos_y = (top + bottom) / 2;
	CFlameEffect* effect = new CFlameEffect(pos_x,pos_y);
	//spawn item here 
	for (int i = 0; i < item.size(); i++) {
		if (item[i] == ITEMCODE_BIGHEART)
		{
			CBigHeart* bigheart = new CBigHeart(pos_x, pos_y);
			CGameObject::AddObject(bigheart);
		}
	}
}