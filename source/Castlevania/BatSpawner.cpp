#include "BatSpawner.h"
#include "Bat.h"
bool CBatSpawner::ShouldSpawn()
{
	int temp = isBarelyOffscreen();
	if (temp == DIRECTION_LEFT || temp == DIRECTION_RIGHT)
	{
		spawn_direction = temp;
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