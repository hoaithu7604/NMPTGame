#include "Spawner.h"
CSpawner::CSpawner(float x, float y, float width, float height)
	:CGameObject()
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	state = GAMEOBJECT_STATE_UPDATE_ONLY;
}
void CSpawner::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
};
void CSpawner::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) 
{
	if (ShouldSpawn())
		Spawn();
}