#pragma once
#include <Windows.h>
#include <vector>
//#include "GameObject.h"
#define CAMERA_MODE_INSTANT 0
#define CAMERA_MODE_SLOWLY 1
#define CAMERA_TYPE_FOLLOW 0 // follow object, but now just need to follow simon :/
#define CAMERA_TYPE_TARGET 1 // set target at certain point
#define CAMERA_SPEED_DEFAULT 0.15f
using namespace std;
class CCamera {
	static CCamera * __instance;
	float x;
	float y;
	float Width;
	float Height;
	float targetX;
	float targetY;
	int mode;
	int type;
	float speed = CAMERA_SPEED_DEFAULT;
	vector<RECT> cameraBounds;
	bool ignoreBound = false; // ignore camera bound if this flag is true
public:
	void IgnoreBound(bool b = true) { ignoreBound = b; }
	void SetType(int type) { this->type = type; }
	void SetMode(int mode) { this->mode = mode; }
	void SetTarget(float x, float y) { targetX = x; targetY = y; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void SetSize(float width, float height) { this->Width = width; this->Height = height; }
	void GetSize(float &width, float &height) { width = this->Width; height = this->Height; }
	void GetViewSize(float &top, float&left, float&bottom, float&right) { top = y; left = x; bottom = y + Height; right = x + Width; }
	void Focus(float x, float y);
	void Update(DWORD dt);
	RECT GetContainBound(float x, float y);
	void AddCameraBound(float left, float top, float right, float bottom);
	static CCamera*GetInstance();
};