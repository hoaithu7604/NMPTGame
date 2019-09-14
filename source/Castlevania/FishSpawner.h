#pragma once
#include "Spawner.h"
#define FISH_SPAWNER_COOLDOWN 20000 
#define FISH_SHOOTING_FORCE 0.7f
class CFishSpawner : public CSpawner
{
	int spawn_direction;
public:
	virtual bool ShouldSpawn();
	virtual void Spawn();
	CFishSpawner() :CSpawner() { cooldown_timer.SetTime(FISH_SPAWNER_COOLDOWN); }
	CFishSpawner(float x, float y, float width, float height) :CSpawner(x, y, width, height) { cooldown_timer.SetTime(FISH_SPAWNER_COOLDOWN); }
};