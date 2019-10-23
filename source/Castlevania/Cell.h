#pragma once
#include "GameObject.h"
#include <vector>
class CCell
{
	vector<LPGAMEOBJECT> objects;
public:
	CCell() {  }
	void AddObject(LPGAMEOBJECT obj) { objects.push_back(obj); }
	void GetObjects(vector<LPGAMEOBJECT>& objects);
};