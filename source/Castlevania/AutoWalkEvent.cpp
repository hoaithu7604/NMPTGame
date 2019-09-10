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
	if (abs(x-targetX)>MIN_DISTANCE)
	{
		if (simon->isMoveable())
		{
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
		isTriggering = false;
		simon->ForceIdle();
		simon->ReleaseControl();
	}
}
