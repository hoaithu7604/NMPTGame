#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#define ITEMCODE_BIGHEART "bigheart"
using namespace std;

class CItemHolder : public CGameObject
{
protected:
	vector<string> item;
public:
	CItemHolder() { state = GAMEOBJECT_STATE_ACTIVE; }
	void Destroy();
	void AddItem(string item) { this->item.push_back(item); }
	virtual void Render() { if (isOnCamera()) CGameObject::Render(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
};