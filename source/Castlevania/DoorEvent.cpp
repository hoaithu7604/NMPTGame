#include "DoorEvent.h"
#include "Simon.h"
#include "Camera.h"
#include "Monster.h"
CDoorEvent::CDoorEvent(float x, float y, float width, float height,
	float cameraX, float cameraY, float doorX, float doorY,
	float targetX, float targetY, float finishX,float finishY)
	:CEventObject(x, y, width, height)
{
	this->cameraX = cameraX;
	this->cameraY = cameraY;
	this->targetX = targetX;
	this->targetY = targetY;
	this->finishX = finishX;
	this->finishY = finishY;
	gate = new CGate();
	gate->SetPosition(doorX, doorY);
	dummyGate = new CUnseenForce(doorX, doorY, GATE_BBOX_WIDTH, GATE_BBOX_HEIGHT);
	CGameObject::AddObject(gate);
	CGameObject::AddObject(dummyGate);
	openDelayTimer.SetTime(DOOR_OPEN_DELAY);
	walkDelayTimer.SetTime(WALK_DELAY);
	closeDelayTimer.SetTime(DOOR_CLOSE_DELAY);
	cameraReturnTimer.SetTime(CAMERA_RETURN_DELAY);
	finishDelayTimer.SetTime(FINISH_DELAY);
}

bool CDoorEvent::ShouldTrigger()
{
	return isTriggering || isContaining(CSimon::GetInstance());
}
void CDoorEvent::Trigger()
{
	CSimon*simon = CSimon::GetInstance();
	if (!isTriggering)
	{
		//event started
		isTriggering = true;
		simon->BlockControl();
		simon->ForceIdle();
		openDelayTimer.Active();
		simon->SetFacing(DIRECTION_RIGHT);
		//setup camera
		CCamera* camera = CCamera::GetInstance();
		camera->IgnoreBound();
		camera->SetTarget(cameraX, cameraY);
		camera->SetMode(CAMERA_MODE_SLOWLY);
		camera->SetType(CAMERA_TYPE_TARGET);
	}
	if (openDelayTimer.hasTicked())
	{
		//open door
		gate->Open();
		walkDelayTimer.Active();
	}
	if (walkDelayTimer.hasTicked())
	{
		// start to walk
		dummyGate->SetState(GAMEOBJECT_STATE_INVISIBLE);
		simon->AutoMove(targetX, targetY,DOOR_EVENT_SPEED);
		closeDelayTimer.Active();
	}
	if (closeDelayTimer.hasTicked())
	{
		//close door
		gate->Close();
		dummyGate->SetState(GAMEOBJECT_STATE_COLLIDABLE);
		cameraReturnTimer.Active();
	}
	if (cameraReturnTimer.hasTicked())
	{
		//move camera
		CCamera* camera = CCamera::GetInstance();
		camera->SetTarget(finishX, finishY); 
		finishDelayTimer.Active();
	}
	if (finishDelayTimer.hasTicked())
	{
		isTriggering = false;
		//set camera back to where it should be
		CCamera* camera = CCamera::GetInstance();
		camera->IgnoreBound(false);
		camera->SetMode(CAMERA_MODE_INSTANT);
		camera->SetType(CAMERA_TYPE_FOLLOW);
		simon->ReleaseControl(); // you're done my man
	}
	
}

void CDoorEvent::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (ShouldTrigger())
	{
		Trigger();
		for (int i = 0; i < coObjects->size(); i++)
		{
			CGameObject*obj = coObjects->at(i);
			if (dynamic_cast<CMonster*>(obj)&&(obj->isAlmostOnCamera()))
				coObjects->at(i)->SetState(GAMEOBJECT_STATE_INVISIBLE); // remove all monster while this event is active
		}
	}
}