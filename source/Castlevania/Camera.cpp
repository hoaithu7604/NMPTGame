#include "Camera.h"
#include "Simon.h"
CCamera* CCamera::__instance = NULL;
CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}
void CCamera::Focus(float x, float y)
{
	RECT activeBound = GetContainBound(x, y);

	this->x = x - Width / 2;
	this->y = y - Height / 2;
	if (this->x < activeBound.left) this->x = activeBound.left;
	if (this->y < activeBound.top) this->y = activeBound.top;
	if (this->x > activeBound.right - Width) this->x = activeBound.right - Width;
	if (this->y > activeBound.bottom - Height) this->y = activeBound.bottom - Height;
}
RECT CCamera::GetContainBound(float x, float y) {
	for (int i = 0; i < cameraBounds.size(); i++)
		if (x >= cameraBounds[i].left&&y >= this->cameraBounds[i].top&&x <= this->cameraBounds[i].right&&y <= cameraBounds[i].bottom)
			return cameraBounds[i];
		
	RECT temp;
	temp.top = temp.right = temp.bottom = temp.left = 0;
	return temp;
}
void CCamera::AddCameraBound(float left, float top, float right, float bottom)
{
	RECT rect;
	rect.top = top;
	rect.left = left;
	rect.right = right;
	rect.bottom = bottom;
	cameraBounds.push_back(rect);
}
void CCamera::Update(DWORD dt)
{
	switch (type) {
	case CAMERA_TYPE_FOLLOW:
		CSimon::GetInstance()->GetCentralPoint(targetX, targetY);
		break;
	}
	// get the active bound contains target point
	RECT activeBound = GetContainBound(targetX, targetY);

	// the point the camera is supposed to be
	float _targetX = targetX - Width / 2;
	float _targetY = targetY - Height / 2;
	

	switch (mode) {
	case CAMERA_MODE_INSTANT:
		this->x = _targetX;
		this->y = _targetY;
		break;
	case CAMERA_MODE_SLOWLY:
		//distance between target point and camera
		float d = sqrt((_targetX - x)*(_targetX - x) + (_targetY - y)*(_targetY - y));
		float t = speed / d;
		if (dt*t < 1)
		{
			//have not reached yet
			this->x += (_targetX - x)*t*dt;
			this->y += (_targetY - y)*t*dt;
		}
		else
		{
			//reached
			this->x = _targetX;
			this->y = _targetY;
		}
		break;
	}
	//valid with bound
	if (!ignoreBound)
	{
		if (this->x < activeBound.left) this->x = activeBound.left;
		if (this->y < activeBound.top) this->y = activeBound.top;
		if (this->x > activeBound.right - Width) this->x = activeBound.right - Width;
		if (this->y > activeBound.bottom - Height) this->y = activeBound.bottom - Height;
	}
	x = (int)x;
	y = (int)y;
}