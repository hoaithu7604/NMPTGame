#pragma once
#include "EffectObject.h"
#define FIREBALL_BBOX_WIDTH 14
#define FIREBALL_BBOX_HEIGHT 12
#define FIREBALL_LAST_TIME 100000
#define FIREBALL_SPEED 0.20f
#define FIREBALL_DAMAGE 1
#define FIREBALL_HEALTH 1
enum class FireBallAnim {
	RIGHT = 2400,
	LEFT
};
class CFireBall : public CEffectObject
{
	float vx, vy; 
	int contactDamage = FIREBALL_DAMAGE;
public:
	int GetContactDamage() { return contactDamage; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CFireBall(float x, float y,float nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Destroy();
};
