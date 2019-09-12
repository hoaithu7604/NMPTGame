#pragma once
#include "Monster.h"
#define HOUND_BBOX_WIDTH 48
#define HOUND_BBOX_HEIGHT 32
#define HOUND_RUNNING_SPEED 0.5f
#define HOUND_POINT 100
#define HOUND_CONTACT_DAMAGE 1
#define HOUND_HEALTH_DEFAULT 1
#define HOUND_JUMPSCARE_DISTANCE 50
#define HOUND_JUMP_SPEED 0.5f
enum class HoundAnimID {
	IDLE_LEFT,
	IDLE_RIGHT,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT
};
class CHound : public CMonster
{
	bool isJumping;
public:
	CHound();
	CHound(float x, float y, float nx);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
};