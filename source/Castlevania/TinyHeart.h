#pragma once
#include "ItemObject.h"
#define ITEM_TINYHEART_POINT 0
#define ITEM_TINYHEART_BBOX_WIDTH 16
#define ITEM_TINYHEART_BBOX_HEIGHT 20 // 16
#define ITEM_TINYHEART_HEART_VALUE 1
#define ITEM_TINYHEART_ACCELERATION_X 0.001
#define ITEM_TINYHEART_VELOCITY_X_MAX 0.1
#define ITEM_TINYHEART_GRAVITY 0.0001f
enum class TinyHeartAnimID {
	IDLE=1200
};
class CTinyHeart : public CItemObject
{
	float accelerationX=ITEM_TINYHEART_ACCELERATION_X;
public:
	CTinyHeart() :CItemObject(ITEM_TINYHEART_POINT) { currentAnim = (int)TinyHeartAnimID::IDLE; prevAnim = (int)TinyHeartAnimID::IDLE; };
	CTinyHeart(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetReward();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};