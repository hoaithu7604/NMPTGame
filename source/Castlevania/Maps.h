#pragma once
#include "TiledMap.h"
/*
Tiled Map Manager class
*/
class CMaps {
	static CMaps * __instance;
	vector<LPTILEDMAP> maps;
	int currentMap;
public:
	void Add(LPTILEDMAP map) { maps.push_back(map); }
	LPTILEDMAP GetCurrentMap() { return this->maps[currentMap]; }
	void SetCurrentMap(int index) { this->currentMap = index; }

	static CMaps * GetInstance();
};
