#include "Cell.h"

void CCell::GetObjects(vector<LPGAMEOBJECT>& objects)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		objects.push_back(this->objects.at(i));
	}
}