#pragma once
#include "Cell.h"
#include <unordered_set>
#define CELL_HEIGHT 256
#define CELL_WIDTH 256
class CGrid
{
	vector<vector<CCell*>> cells;

	int rows;
	int columns;
	static CGrid* __instance;
	int staR;
	int staC;
	int endR;
	int endC;

	unordered_set<LPGAMEOBJECT> activeObjects;
public:
	CGrid() {}
	CGrid(int mapWidth, int mapHeight);
	void Add(LPGAMEOBJECT obj);
	void UpdateActiveCells(float, float, float, float);
	void UpdateActiveObjects();
	void UpdateCells();
	void GetActiveObjects(vector<LPGAMEOBJECT>&objects);
	void GetUpdatableObjects(vector<LPGAMEOBJECT>&objects);
	void GetColliableObjects(vector<LPGAMEOBJECT>&objects);
	void GetCells(float, float, float, float, int&, int&, int&, int&);
	static CGrid* GetInstance();
	static void SetInstance(CGrid*);
};