#include "StairUp.h"
#include "Simon.h"
CStairUp::CStairUp(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->startX = x;
	this->startY = y + height;
	this->endX = x + width;
	this->endY = y;
}
bool CStairUp::isAbleToClimb()
{
	float x, y;
	CSimon::GetInstance()->GetCentralPoint(x, y);
	return sqrt((startX - x)*(startX - x) + (startY - y)*(startY - y)) < ABLE_TO_CLIMB_DISTANCE
		|| sqrt((endX - x)*(endX - x) + (endY - y)*(endY - y)) < ABLE_TO_CLIMB_DISTANCE;
}
