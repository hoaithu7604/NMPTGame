#include "UnseenForce.h"

CUnseenForce::CUnseenForce(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width= width;
	this->height = height;
	state = GAMEOBJECT_STATE_ACTIVE;
	currentAnim = -1;
}
void CUnseenForce::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = this->x;
	top = this->y;
	right = left + width;
	bottom = top + height;
}
