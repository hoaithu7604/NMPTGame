#pragma once
#include "GameObject.h"
#include <vector>
#include <unordered_set>
class CCell
{
	vector<LPGAMEOBJECT> objects;
public:
	CCell() {  }
	void AddObject(LPGAMEOBJECT obj) { objects.push_back(obj); }
	void GetObjects(vector<LPGAMEOBJECT>& objects);
	void GetObjects(unordered_set<LPGAMEOBJECT>& objects);
	void ClearObjects() { objects.clear(); }
};