#include "Cell.h"

void CCell::GetObjects(vector<LPGAMEOBJECT>& objects)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		objects.push_back(this->objects.at(i));
	}
}
void CCell::GetObjects(unordered_set<LPGAMEOBJECT>& objects)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		objects.insert(this->objects.at(i));
	}
}