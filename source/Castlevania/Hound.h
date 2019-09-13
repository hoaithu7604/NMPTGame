#pragma once
#include "Monster.h"
#define HOUND_BBOX_WIDTH 48
#define HOUND_BBOX_HEIGHT 32
#define HOUND_RUNNING_BBOX_WIDTH 64
#define HOUND_RUNNING_BBOX_HEIGHT 32
#define HOUND_RUNNING_SPEED 0.2f
#define HOUND_POINT 100
#define HOUND_CONTACT_DAMAGE 1
#define HOUND_HEALTH_DEFAULT 1
#define HOUND_JUMPSCARE_DISTANCE 120
#define HOUND_JUMP_SPEED 0.35f
enum class HoundAnimID {
	IDLE_RIGHT=1400,
	IDLE_LEFT,
	RUN_RIGHT,
	RUN_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT
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