#include "ItemHolder.h"
#include "FlameEffect.h"

void CItemHolder::Destroy() {
	state = GAMEOBJECT_STATE_INVISIBLE;
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	CFlameEffect* effect = new CFlameEffect((left+right)/2, (top+bottom)/2);

	//spawn item here 
}