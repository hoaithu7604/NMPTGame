#include "EventObject.h"

CEventObject::CEventObject(float x, float y, float width, float height)
	:CGameObject()
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	state = GAMEOBJECT_STATE_UPDATE_ONLY;
}
void CEventObject::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}
void CEventObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (ShouldTrigger())
		Trigger();
}