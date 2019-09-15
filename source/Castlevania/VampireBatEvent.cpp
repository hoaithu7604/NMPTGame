#include "VampireBatEvent.h"
#include "Simon.h"
#include "OverlayBoard.h"
#include "MagicCrystal.h"
CVampireBatEvent::CVampireBatEvent(float x, float y, float width, float height,
	float cameraX, float cameraY, float batX, float batY)
	:CEventObject(x,y,width,height)
{
	isTriggered = false;
	this->cameraX = cameraX;
	this->cameraY = cameraY;
	//spawn bat here
	bat = new CVampireBat(batX, batY);
	CGameObject::AddObject(bat);
	//wall around arena
	top = new CUnseenForce(x, y - WALL_SIZE, width, WALL_SIZE);
	bottom = new CUnseenForce(x, y + height, width, WALL_SIZE);
	left = new CUnseenForce(x - WALL_SIZE, y, WALL_SIZE, height);
	right = new CUnseenForce(x + width, y, WALL_SIZE, height);
	CGameObject::AddObject(top);
	CGameObject::AddObject(bottom);
	CGameObject::AddObject(left);
	CGameObject::AddObject(right);
	DeactiveWall();
	//setup timer;
	wakeDelayTimer.SetTime(WAKE_DELAY);
}
void CVampireBatEvent::Trigger()
{
	if (!isTriggering)
	{
		//start event
		wakeDelayTimer.Active();
		isTriggering = true;
		ActiveWall();
		//set camera
		CCamera*camera = CCamera::GetInstance();
		camera->SetTarget(cameraX, cameraY);
		camera->SetMode(CAMERA_MODE_SLOWLY);
		camera->SetType(CAMERA_TYPE_TARGET);
	}
	else
	{
		if (wakeDelayTimer.hasTicked())
		{
			COverlayBoard::GetInstance()->SetBoss(bat);
			bat->Wake();
		}
		if (bat->GetState() == GAMEOBJECT_STATE_INVISIBLE)
		{
			//end event here
			//create reward
			DeactiveWall();
			float posX, posY;
			posX = x + width / 2;
			posY = y + height / 2;
			CGameObject::AddObject(new CMagicCrystal(posX, posY));
			CCamera*camera = CCamera::GetInstance();
			camera->SetMode(CAMERA_MODE_INSTANT);
			camera->SetType(CAMERA_TYPE_FOLLOW);
			isTriggering = false;
			isTriggered = true;
		}
	}
}
bool CVampireBatEvent::ShouldTrigger()
{
	return (isTriggering || isContaining(CSimon::GetInstance()))&&!isTriggered;
}

void CVampireBatEvent::DeactiveWall()
{
	top->SetState(GAMEOBJECT_STATE_INVISIBLE);
	bottom->SetState(GAMEOBJECT_STATE_INVISIBLE);
	left->SetState(GAMEOBJECT_STATE_INVISIBLE);
	right->SetState(GAMEOBJECT_STATE_INVISIBLE);
}
void CVampireBatEvent::ActiveWall()
{
	top->SetState(GAMEOBJECT_STATE_COLLIDABLE);
	bottom->SetState(GAMEOBJECT_STATE_COLLIDABLE);
	left->SetState(GAMEOBJECT_STATE_COLLIDABLE);
	right->SetState(GAMEOBJECT_STATE_COLLIDABLE);
}