#pragma once
#include "Spawner.h"
#include "Hound.h"
class CHoundSpawner : public CSpawner
{
	int spawn_direction;
	CHound* hound;
public:
	virtual bool ShouldSpawn();
	virtual void Spawn();
	CHoundSpawner() :CSpawner() { }
	CHoundSpawner(float x, float y, float width, float height) :CSpawner(x, y, width, height) {}

};