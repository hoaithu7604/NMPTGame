#include "HoundSpawner.h"

bool CHoundSpawner::ShouldSpawn()
{
	int temp = isBarelyOffscreen();
	//check if spawner is offscreen and if the hound is still alive
	if ((temp == DIRECTION_LEFT || temp == DIRECTION_RIGHT) && (hound == NULL || hound->IsInvisible()))
	{
		spawn_direction = temp;
		return true;
	}
	else return false;
}

void CHoundSpawner::Spawn()
{
	hound = new CHound(x, y, -spawn_direction);
	CGameObject::AddObject(hound);
}