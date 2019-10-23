#pragma once
#include "Cell.h"
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
public:
	CGrid(int mapWidth, int mapHeight);
	void Add(LPGAMEOBJECT obj);
	void Update(float, float, float, float);
	void UpdateCells();
	void GetCells(float, float, float, float, int&, int&, int&, int&);
	static CGrid* GetInstance();
	static void SetInstance(CGrid*);
};