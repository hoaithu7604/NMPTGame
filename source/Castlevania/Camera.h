#pragma once
#include <Windows.h>
#include <vector>
class CCamera {
	static CCamera * __instance;
	float x;
	float y;
	float Width;
	float Height;
public:
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void SetSize(float width, float height) { this->Width = width; this->Height = height; }
	void GetSize(float &width, float &height) { width = this->Width; height = this->Height; }
	void GetViewSize(float &top, float&left, float&bottom, float&right) { top = y; left = x; bottom = y + Height; right = x + Width; }
	void Focus(float x, float y);
	static CCamera*GetInstance();
};