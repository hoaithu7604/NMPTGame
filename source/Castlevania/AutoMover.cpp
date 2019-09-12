#include "AutoMover.h"
#include "Simon.h"

void CAutoMover::SetTarget(float x, float y)
{
	this->targetX = x;
	this->targetY = y;
}
void CAutoMover::SetTime(DWORD t)
{
	this->timer.SetTime(t);
}
void CAutoMover::Update(DWORD dt)
{
	if (!isActive) return;
	CSimon*simon = CSimon::GetInstance();
	if (mode == AUTO_MOVER_MODE_FORCED)
		simon->BlockControl();
	if (type == AUTO_MOVER_TYPE_DEFAULT)
	{
		float vx, vy;
		float x, y;
		simon->GetPosition(x, y);
		if (GetVelocity(vx, vy, dt))
		{
			if (mode == AUTO_MOVER_MODE_FORCED)
				simon->ReleaseControl();
			isActive = false;
			simon->SetPosition(targetX, targetY);
			simon->SetSpeed(0, 0);
		}
		else simon->SetSpeed(vx, vy);
		if (vx > 0)
			simon->SetFacing(DIRECTION_RIGHT);
		else if (vx < 0)
			simon->SetFacing(DIRECTION_LEFT);
	}
	else if (type == AUTO_MOVER_TYPE_TIMED)
	{
		if (timer.hasTicked())
		{
			if (mode == AUTO_MOVER_MODE_FORCED)
				simon->ReleaseControl();
			isActive = false;
		}
		else
		{
			float vx, vy;
			float x, y;
			simon->GetPosition(x, y);
			GetVelocity(vx, vy,dt);
			simon->SetSpeed(vx, vy);
			if (vx > 0)
				simon->SetFacing(DIRECTION_RIGHT);
			else if (vx < 0)
				simon->SetFacing(DIRECTION_LEFT);
		}
	}

}
void CAutoMover::Active(int mode, int type)
{ 
	isActive = true; 
	if (mode!=-1) SetMode(mode); 
	if (type!=-1) SetType(type);
	if (this->type == AUTO_MOVER_TYPE_TIMED)
	{
		timer.Active();
	}
}
bool CAutoMover::GetVelocity(float&vx, float&vy, DWORD dt)
{
	float x, y;
	CSimon::GetInstance()->GetPosition(x, y);
	float d = sqrt((targetX - x)*(targetX - x) + (targetY - y)*(targetY - y));//distance between target point and simon
	float t = speed / d;
	if (dt*t < 1)
	{
		vx = (targetX - x)*t;
		vy = (targetY - y)*t;
		return false;
	}
	else
	{
		vx = (targetX - x);
		vy = (targetY - y);
		return true;
	}


}