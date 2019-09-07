#pragma once
#include "Simon.h"

CSimon * CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon() 
	:CMoveableObject()
{
	camera = CCamera::GetInstance();
}
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	//



	//

	x += dx;
	y += dy;
	camera->Focus(x, y);
	UpdateCurrentAnim();
}
void CSimon::Render() 
{
	CGameObject::Render();
}
void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{

}
void CSimon::DoAction(Action action)
{
	switch (action) {
		case Action::WALK_LEFT:
			this->nx = -1;
			this->vx = SIMON_WALKING_SPEED * this->nx;
			break;
		case Action::WALK_RIGHT:
			this->nx = 1;
			this->vx = SIMON_WALKING_SPEED * this->nx;
			break;
		case Action::IDLE:
			this->vx = 0;
			break;
	}
}
void CSimon::UpdateCurrentAnim() 
{
	if (vx != 0) {
		currentAnim = nx > 0 ? (int)SimonAnimID::WALK_RIGHT : (int)SimonAnimID::WALK_LEFT;
	}
	else
	{
		currentAnim = nx > 0 ? (int)SimonAnimID::IDLE_RIGHT : (int)SimonAnimID::IDLE_LEFT;
	}
}