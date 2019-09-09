#pragma once

#include <algorithm>
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <fstream>
#include <string>

#include "Animations.h"
#include "Sprites.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"

#define OBJECTDATA_PATH L"Resource\\Objects\\"
using namespace std;

#define ID_TEX_BBOX 100		// special texture to draw object bounding box

#define GAMEOBJECT_STATE_INVISIBLE 0 //no render, no update
#define GAMEOBJECT_STATE_VISIBLE 1  // render only
#define GAMEOBJECT_STATE_ACTIVE 2 //both


class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
	static vector<LPGAMEOBJECT>* objects;
protected:
	int health = 0;
	float x; 
	float y;
	int nx; // >0 right, <=0 left
	int state;
	int currentAnim;
	int prevAnim;
	CARGB argb;
	CAnimations* animations; //Should be fine i guess?
public: 
	bool isOnCamera();
	static void Init(vector<LPGAMEOBJECT>*_objects) { objects = _objects; }
	static void AddObject(LPGAMEOBJECT object) { objects->push_back(object); }
	static void LoadResource(string ObjectName);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	int GetState() { return this->state; }
	virtual void SetState(int state) { this->state = state; }
	int GetHealth() { return health; }
	void RenderBoundingBox();

	CGameObject();
	bool isOverlapping(CGameObject*obj);
	void SetAnimation(int AnimID) { this->currentAnim = AnimID; }
	virtual void FreezeAnimation();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void RenderOverlay();
	
	~CGameObject();
};

