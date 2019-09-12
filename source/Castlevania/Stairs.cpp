#include "Stairs.h"
#include "Simon.h"
CStairs::CStairs(float x1, float y1, float x2, float y2)
{
	state = GAMEOBJECT_STATE_COLLIDABLE;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}
bool CStairs::isAbleToClimb()
{
	float left, top, right, bottom;
	CSimon::GetInstance()->GetBoundingBox(left, top, right, bottom);
	float l1 = x1, t1 = y1, r1 = l1 + STAIR_BBOX_WIDTH, b1 = t1 + STAIR_BBOX_HEIGHT;
	float l2 = x2, t2 = y2, r2 = l2 + STAIR_BBOX_WIDTH, b2 = t2 + STAIR_BBOX_HEIGHT;
	return (l1 < right && r1 > left && t1 < bottom && b1 > top)
		|| (l2 < right && r2 > left && t2 < bottom && b2 > top); //return true if simon overlapping any entrance
}
bool CStairs::ShouldCrouch()
{
	int stair = CheckStair();
	if (stair==FIRST)  // overlapping with first stair
	{
		if (y1 > y2)
			return true;
		else
			return false;
	}
	else if (stair==SECOND) //second
	{
		if (y1 > y2)
			return false;
		else return true;
	}
}
int CStairs::CheckStair()
{
	float left, top, right, bottom;
	CSimon::GetInstance()->GetBoundingBox(left, top, right, bottom);
	float l1 = x1, t1 = y1, r1 = l1 + STAIR_BBOX_WIDTH, b1 = t1 + STAIR_BBOX_HEIGHT;
	float l2 = x2, t2 = y2, r2 = l2 + STAIR_BBOX_WIDTH, b2 = t2 + STAIR_BBOX_HEIGHT;
	if (l1 < right && r1 > left && t1 < bottom && b1 > top)  // overlapping with first stair
		return FIRST;
	else if (l2 < right && r2 > left && t2 < bottom && b2 > top) //second
		return SECOND;
	else return 0; // nope
}
bool CStairs::isAbleToGoUp(float x,float y)
{
	if (x == x1 && y == y1)
	{
		if (y1 > y2) return true;
		else return false;
	}
	else if (x == x2 && y == y2) 
	{
		if (y2 > y1) return true;
		else return false;
	}
	else return true;
}
bool CStairs::isAbleToGoDown(float x, float y)
{
	if (x == x1 && y == y1)
	{
		if (y1 > y2) return false;
		else return true;
	}
	else if (x == x2 && y == y2)
	{
		if (y2 > y1) return false;
		else return true;
	}
	else return true;
}
void CStairs::Up()
{
	CSimon*simon = CSimon::GetInstance();
	if (simon->IsOnStairs())
	{
		float x, y;
		simon->GetPosition(x, y);
		if (isAbleToGoUp(x,y))
		{
			
			OutputDebugString(L"GO UP!!!!!");
			int stair = GetStairsType();
			if (stair==STAIRS_TYPE_UP)
				simon->AutoMove(x + STAIR_STEP_DISTANCE, y - STAIR_STEP_DISTANCE, STAIRS_CLIMBING_SPEED,AUTO_MOVER_MODE_FORCED);
			else 
				simon->AutoMove(x - STAIR_STEP_DISTANCE, y - STAIR_STEP_DISTANCE, STAIRS_CLIMBING_SPEED, AUTO_MOVER_MODE_FORCED);
		}
		else
		{
			simon->SetOnStairs(false);
		}
		
	}
	{
		int stair = CheckStair();
		if (stair == FIRST)
		{
			if (y1 > y2)
			{
				float x, y;
				CSimon::GetInstance()->GetPosition(x, y);
				if (x == x1 && y == y1)
					CSimon::GetInstance()->SetOnStairs();
				else
				CSimon::GetInstance()->AutoMove(x1, y1);
			}
		}
		else if (stair == SECOND)
		{
			if (y2 > y1)
			{
				float x, y;
				CSimon::GetInstance()->GetPosition(x, y);
				if (x == x2 && y == y2)
					CSimon::GetInstance()->SetOnStairs();
				else
					CSimon::GetInstance()->AutoMove(x2, y2);
			}
		}
	}
}
void CStairs::Down()
{
	CSimon*simon = CSimon::GetInstance();
	if (simon->IsOnStairs())
	{
		float x, y;
		simon->GetPosition(x, y);
		if (isAbleToGoDown(x, y))
		{
			OutputDebugString(L"GO DOWN!!!!!");
			int stair = GetStairsType();
			if (stair == STAIRS_TYPE_UP)
				simon->AutoMove(x - STAIR_STEP_DISTANCE, y + STAIR_STEP_DISTANCE, STAIRS_CLIMBING_SPEED, AUTO_MOVER_MODE_FORCED);
			else
				simon->AutoMove(x + STAIR_STEP_DISTANCE, y + STAIR_STEP_DISTANCE, STAIRS_CLIMBING_SPEED, AUTO_MOVER_MODE_FORCED);
		}
		else
		{
			simon->SetOnStairs(false);
		}

	}
	{
		int stair = CheckStair();
		if (stair == SECOND)
		{
			if (y1 > y2)
			{
				float x, y;
				CSimon::GetInstance()->GetPosition(x, y);
				if (x == x2 && y == y2)
					CSimon::GetInstance()->SetOnStairs();
				else
					CSimon::GetInstance()->AutoMove(x2, y2);
			}
		}
		else if (stair == FIRST)
		{
			if (y2 > y1)
			{
				float x, y;
				CSimon::GetInstance()->GetPosition(x, y);
				if (x == x1 && y == y1)
					CSimon::GetInstance()->SetOnStairs();
				else
					CSimon::GetInstance()->AutoMove(x1, y1);
			}
		}
	}
}
int CStairs::GetStairsType()
{
	return (y1 > y2) ? STAIRS_TYPE_UP : STAIRS_TYPE_DOWN;
}
bool CStairs::isEntrance()
{
	float x, y;
	CSimon::GetInstance()->GetPosition(x, y);
	return (x == x1 && y == y1) || (x == x2 && y == y2);
}
bool CStairs::ShouldIdle(float x, float y, int nx)
{
	if (x == x1 && y == y1)
	{
		if (y1 < y2)
			return true;
		else return false;
	}
	if (x == x2 && y == y2)
	{
		if (y2 < y1)
			return true;
		else return false;
	}
	else return false;
}