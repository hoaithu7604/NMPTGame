#include "Grid.h"

CGrid::CGrid(int mapWidth, int mapHeight)
{
	this->columns = (mapWidth % CELL_WIDTH == 0) ?
		mapWidth / CELL_WIDTH :
		mapWidth / CELL_WIDTH + 1;
	this->rows = (mapHeight % CELL_HEIGHT == 0) ?
		mapHeight / CELL_HEIGHT :
		mapHeight / CELL_HEIGHT + 1;
	cells.resize(columns);
	for (UINT i = 0; i < cells.size(); ++i)
		cells[i].resize(rows, new CCell());
}
void CGrid::Add(LPGAMEOBJECT obj)
{
	int staC, staR, endC, endR;
	float left, top, right, bottom;
	obj->GetBoundingBox(left, top, right, bottom);
	GetCells(left, top, right, bottom, staC, staR, endC, endR);
	for (int column = staC; column <= endC; column++)
	{
		for (int row = staR; row <= endR; row++)
		{
			cells[column][row]->AddObject(obj);
		}
	}
	activeObjects.insert(obj);
}
void CGrid::UpdateActiveCells(float left, float top, float right, float bottom)
{
	staC = (left < 0) ? 0 : left / CELL_WIDTH;
	staR = (top < 0) ? 0 : top / CELL_HEIGHT;

	endC = (right / CELL_WIDTH < columns) ? (right / CELL_WIDTH) : columns - 1;
	endR = (bottom / CELL_HEIGHT < rows) ? (bottom / CELL_HEIGHT) : rows - 1;
}
void CGrid::UpdateCells() 
{
	for (int column = staC; column <= endC; column++)
	{
		for (int row = staR; row <= endR; row++)
		{
			cells[column][row]->ClearObjects();
		}
	}
	for (auto obj = activeObjects.begin(); obj != activeObjects.end(); ++obj)
	{
		Add(*obj);
	}

}
void CGrid::GetCells(float left, float top, float right, float bottom,
	int&staC, int&staR, int &endC, int &endR)
{
	staC = (left < 0) ? 0 : left / CELL_WIDTH;
	staR = (top < 0) ? 0 : top / CELL_HEIGHT;

	endC = (right / CELL_WIDTH < columns) ? (right / CELL_WIDTH) : columns - 1;
	endR = (bottom / CELL_HEIGHT < rows) ? (bottom / CELL_HEIGHT) : rows - 1;
}
CGrid* CGrid::GetInstance()
{
	return __instance;
}
void CGrid::SetInstance(CGrid* grid)
{
	__instance = grid;
}
CGrid* CGrid::__instance = NULL;
void CGrid::UpdateActiveObjects()
{
	activeObjects.clear();
	for (int column = staC; column <= endC; column++)
	{
		for (int row = staR; row <= endR; row++)
		{
			this->cells[column][row]->GetObjects(activeObjects);
		}
	}
}
void CGrid::GetActiveObjects(vector<LPGAMEOBJECT>&objects)
{
	for (auto obj = activeObjects.begin(); obj != activeObjects.end(); ++obj)
		objects.push_back(*obj);
}
void CGrid::GetUpdatableObjects(vector<LPGAMEOBJECT>&objects)
{
	for (auto obj = activeObjects.begin(); obj != activeObjects.end(); ++obj)
		if ((*obj)->IsUpdatable()) objects.push_back(*obj);
}
void CGrid::GetColliableObjects(vector<LPGAMEOBJECT>&objects)
{
	for (auto obj = activeObjects.begin(); obj != activeObjects.end(); ++obj)
		if ((*obj)->IsColliable()) objects.push_back(*obj);
}
