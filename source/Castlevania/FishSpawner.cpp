#include "FishSpawner.h"
#include "Fish.h"
bool CFishSpawner::ShouldSpawn()
{
	spawn_direction = isBarelyOffscreen();
	if (spawn_direction == DIRECTION_DOWN)
	{
		if (!cooldown_timer.isActive() || cooldown_timer.hasTicked())
		{
			cooldown_timer.Active();
			return true;
		}
	}
	return false;

}
void CFishSpawner::Spawn()
{
	float x, y;
	GetCentralPoint(x, y);
	CGameObject::AddObject(new CFish(x, y, -FISH_SHOOTING_FORCE));
}