#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "Timer.h"
#define ITEMCODE_BIGHEART "bigheart"
#define ITEM_DEFAULT_SPAWN_DELAY 200 // delay time to spawn item
using namespace std;

class CItemHolder : public CGameObject
{
protected:
	vector<string> item;
	CTimer delay_timer;
public:
	CItemHolder() { delay_timer.SetTime(ITEM_DEFAULT_SPAWN_DELAY); state = GAMEOBJECT_STATE_ACTIVE; }
	void Destroy();
	void AddItem(string item) { this->item.push_back(item); }
	virtual void Render() { if (isOnCamera()) CGameObject::Render(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};