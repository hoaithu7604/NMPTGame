#pragma once
#include "GameObject.h"
#define STAIR_BBOX_WIDTH 32
#define STAIR_BBOX_HEIGHT 64
#define STAIR_STEP_DISTANCE 16
#define FIRST 1
#define SECOND 2
#define STAIRS_TYPE_UP 1 // up means / stairs
#define STAIRS_TYPE_DOWN 2 // down means \ stairs
#define STAIRS_CLIMBING_SPEED 0.075f
class CStairs :public CGameObject
{
	float x1;
	float y1;
	float x2;
	float y2;
public:
	CStairs(float x1, float y1, float x2, float y2 );
	bool isEntrance(); // 
	bool isAbleToClimb(); // check if simon is able to climb this stairs
	bool ShouldCrouch(); // check if simon can crouch if overlapping this stairs
	int CheckStair(); //  check which stair is in contact with simon
	int GetStairsType();
	bool isAbleToGoUp(float x, float y);
	bool isAbleToGoDown(float x, float y);
	void Up();
	void Down();
	bool ShouldIdle(float x,float y,int nx); //this is not good, but i have no others way to do it
};