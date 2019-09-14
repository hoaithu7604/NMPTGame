#pragma once
#include "Spawner.h"
#define BAT_SPAWNER_COOLDOWN 10000 
class CBatSpawner : public CSpawner
{
	int spawn_direction;
public:
	virtual bool ShouldSpawn();
	virtual void Spawn();
	CBatSpawner() :CSpawner() { cooldown_timer.SetTime(BAT_SPAWNER_COOLDOWN); }
	CBatSpawner(float x, float y, float width, float height) :CSpawner(x, y, width, height) { cooldown_timer.SetTime(BAT_SPAWNER_COOLDOWN); }

};