#include "BatSpawner.h"
#include "Bat.h"
bool CBatSpawner::ShouldSpawn()
{
	spawn_direction = isBarelyOffscreen();
	if (spawn_direction == DIRECTION_LEFT || spawn_direction == DIRECTION_RIGHT)
	{
		if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
		{
			cooldown_timer.Active();
			return true;
		}
	}
	return false;

}
void CBatSpawner::Spawn()
{		
	float x, y;
	GetCentralPoint(x, y);
	CGameObject::AddObject(new CBat(x, y, -spawn_direction)); 
}