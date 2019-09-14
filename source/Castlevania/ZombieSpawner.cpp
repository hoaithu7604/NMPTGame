#include "ZombieSpawner.h"
#include "Zombie.h"
bool CZombieSpawner::ShouldSpawn()
{
	spawn_direction = isBarelyOffscreen();
	if (spawn_direction == DIRECTION_LEFT || spawn_direction == DIRECTION_RIGHT)
	{
		if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
		{
			cooldown_timer.Active();
			delay_timer.Reset();
			counter = ZOMBIE_SPAWNER_COUNT_MAX;
			return true;
		}
	}
	return delay_timer.hasTicked();

}
void CZombieSpawner::Spawn()
{
	if (counter > 0)
	{
		if (!delay_timer.isActive() || delay_timer.hasTicked())
		{
			counter--;
			if (spawn_direction != 0)
			{
				OutputDebugString(L"SPAWN ZOMBIE");
				float x, y;
				GetCentralPoint(x, y);
				CGameObject::AddObject(new CZombie(x, y, -spawn_direction)); //make zombie face to camera
				//spawn zombie here;
			}
			else OutputDebugString(L"[INFO]SHOULD SPAWN BUT ALREADY ONSCREEN");
			if (counter > 0)
				delay_timer.Active();
			else delay_timer.Reset();
		}
	}
}