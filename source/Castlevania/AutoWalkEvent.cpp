#include "AutoWalkEvent.h"
#include "Simon.h"
bool CAutoWalkEvent::ShouldTrigger()
{
	return isTriggering||isContaining(CSimon::GetInstance());
}
void CAutoWalkEvent::Trigger()
{
	isTriggering = true;
	CSimon*simon = CSimon::GetInstance();
	float x, y;
	simon->GetPosition(x, y);
	//simon->AutoMoverSetTime(1000);
	//simon->AutoMove(targetX, targetY, AUTO_WALK_SPEED, AUTO_MOVER_MODE_FORCED,AUTO_MOVER_TYPE_TIMED);
	if (abs(x-targetX)>MIN_DISTANCE)
	{
		if (simon->isMoveable())
		{
			simon->BlockControl();
			if (targetX - x > 0)
			{
				simon->SetSpeed(AUTO_WALK_SPEED, 0);
				simon->SetFacing(DIRECTION_RIGHT);
			}
			else
			{
				simon->SetSpeed(-AUTO_WALK_SPEED, 0);
				simon->SetFacing(DIRECTION_LEFT);
			}
		}
		else 
		{
			simon->ForceIdle();
			simon->BlockControl(); 
		}
	}
	else
	{
		simon->SetPosition(targetX, targetY);
		isTriggering = false;
		simon->ForceIdle();
		simon->ReleaseControl();
	}
}
