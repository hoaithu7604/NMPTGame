#include "Camera.h"
CCamera* CCamera::__instance = NULL;
CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}
void CCamera::Focus(float x, float y)
{
	this->x = x - Width / 2;
	this->y = y - Height / 2;
}