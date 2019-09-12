#include "Camera.h"
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