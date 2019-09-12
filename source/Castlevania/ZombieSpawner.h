#pragma once
#include "Spawner.h"
#define ZOMBIE_SPAWNER_COOLDOWN 20000 
#define ZOMBIE_SPAWNER_DELAY 300 // delay between each zombie
#define ZOMBIE_SPAWNER_COUNT_MAX 3
class CZombieSpawner : public CSpawner
{
	CTimer delay_timer;
	int counter = ZOMBIE_SPAWNER_COUNT_MAX;
	int spawn_direction;
public:
	virtual bool ShouldSpawn();
	virtual void Spawn();
	CZombieSpawner() :CSpawner() { delay_timer.SetTime(ZOMBIE_SPAWNER_DELAY); cooldown_timer.SetTime(ZOMBIE_SPAWNER_COOLDOWN); }
	CZombieSpawner(float x, float y, float width, float height) :CSpawner(x, y, width, height) { delay_timer.SetTime(ZOMBIE_SPAWNER_DELAY); cooldown_timer.SetTime(ZOMBIE_SPAWNER_COOLDOWN); }
	
};