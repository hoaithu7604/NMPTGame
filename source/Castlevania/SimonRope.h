#pragma once
#include "MoveableObject.h"
#define SIMON_ROPE_LEVEL_ONE 1 
#define SIMON_ROPE_LEVEL_TWO 2
#define SIMON_ROPE_LEVEL_THREE 3
#define SIMON_ROPE_LEVEL_DEFAULT 1
#define SIMON_ROPE_LEVEL_ONE_LAST_FRAME_BBOX_WIDTH 56
#define SIMON_ROPE_LEVEL_ONE_LAST_FRAME_BBOX_HEIGHT 18
#define SIMON_ROPE_LEVEL_TWO_LAST_FRAME_BBOX_WIDTH 56
#define SIMON_ROPE_LEVEL_TWO_LAST_FRAME_BBOX_HEIGHT 18
#define SIMON_ROPE_LEVEL_THREE_LAST_FRAME_BBOX_WIDTH 89
#define SIMON_ROPE_LEVEL_THREE_LAST_FRAME_BBOX_HEIGHT 18
#define SIMON_ROPE_TWO_FIRST_FRAME_BBOX_WIDTH 32
#define SIMON_ROPE_LAST_FRAME_ADJUSTING_Y 14
enum class RopeAnimID
{
	LEVEL_ONE_RIGHT = 200,
	LEVEL_ONE_LEFT,
	LEVEL_TWO_RIGHT,
	LEVEL_TWO_LEFT,
	LEVEL_THREE_RIGHT,
	LEVEL_THREE_LEFT,
};
class CSimonRope : public CGameObject
{
	bool _isActive;
	int level;
	bool isFirstFrame;
public:
	CSimonRope();
	bool isActive() { return _isActive; }
	void Active(bool active = true) { isFirstFrame = true; _isActive = active; }
	void UpdateCurrentAnim();
	void UpdatePosition();
	bool isOverlapping(CGameObject*obj);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(float x, float y, DWORD nx, DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};
typedef CSimonRope* LPSIMONROPE;