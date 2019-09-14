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

#define GAMEOBJECT_STATE_INVISIBLE State(false) //no render, no update, no collision
#define GAMEOBJECT_STATE_VISIBLE State(1,0,0)  // render only
#define GAMEOBJECT_STATE_COLLIDABLE State(0,0,1) //collision only
#define GAMEOBJECT_STATE_ACTIVE State(true) // render, update, collision
#define GAMEOBJECT_STATE_UPDATE_ONLY State(0,1,0) // update only
#define GAMEOBJECT_STATE_NO_UPDATE State(1,0,1)
#define GAMEOBJECT_STATE_NO_RENDER State(0,1,1)
#define GAMEOBJECT_STATE_NO_COLLISION State(1,1,0)
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1
#define DIRECTION_DOWN 2
#define BARELY_OFFSCREEN_DISTANCE 50
struct State
{
	bool renderable;
	bool updatable;
	bool collidable;
	State(bool state=true) :renderable(state), updatable(state), collidable(state) {};
	State(bool renderable, bool updatable, bool collidable) :renderable(renderable), updatable(updatable), collidable(collidable) {};
	bool IsRenderable() { return renderable; }
	bool IsUpdatable() { return updatable; }
	bool IsColliable() { return collidable; }
	bool operator==(const State& other) { 
		return this->renderable == other.renderable&&this->updatable == other.updatable&&this->collidable == other.collidable;
	}
};

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
	State state;
	int health = 0;
	float x; 
	float y;
	int nx; // >0 right, <=0 left
	int currentAnim;
	int prevAnim;
	CARGB argb;
	CAnimations* animations; //Should be fine i guess?
public: 
	CGameObject();
	//checking
	bool isOnCamera();
	bool isAlmostOnCamera();
	int isBarelyOffscreen();
	bool isFarOffscreen();
	bool IsRenderable() { return state.IsRenderable(); }
	bool IsUpdatable() { return state.IsUpdatable(); }
	bool IsColliable() { return state.IsColliable(); }
	bool IsInvisible() { return state == GAMEOBJECT_STATE_INVISIBLE; }
	void SetFacing(int nx) { this->nx = nx; }
	bool isOverlapping(CGameObject*obj);
	bool isContaining(CGameObject*obj);
	float Distance(CGameObject*obj);
	//
	static void Init(vector<LPGAMEOBJECT>*_objects) { objects = _objects; }
	static void AddObject(LPGAMEOBJECT object) { objects->push_back(object); }
	static void LoadResource(string ObjectName);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	State GetState() { return this->state; }
	int GetDirection() { return nx; }
	virtual void SetState(State state) { this->state = state; }
	int GetHealth() { return health; }
	
	void SetAnimation(int AnimID) { this->currentAnim = AnimID; }
	virtual void TakeDamage(int damage);
	virtual void Destroy() {};
	virtual void FreezeAnimation();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) { left = x; top = y; right = x; bottom = y; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void RenderOverlay();
	virtual void GetCentralPoint(float &x, float&y);
	virtual void SetPositionCentral(float x, float y);
	void RenderBoundingBox();
	~CGameObject();
};

