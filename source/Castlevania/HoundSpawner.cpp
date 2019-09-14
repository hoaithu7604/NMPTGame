#include "HoundSpawner.h"

bool CHoundSpawner::ShouldSpawn()
{
	spawn_direction = isBarelyOffscreen();
	//check if spawner is offscreen and if the hound is still alive
	if ((spawn_direction == DIRECTION_LEFT || spawn_direction == DIRECTION_RIGHT) && (hound == NULL || hound->IsInvisible()))
	{
		return true;
	}
	else return false;
}

void CHoundSpawner::Spawn()
{
	hound = new CHound(x, y, -spawn_direction);
	CGameObject::AddObject(hound);
}