#pragma once
#include "GameObject.h"
class CUnseenForce : public CGameObject 
{
	float width;
	float height;
	float bottom;
	float right;
public:
	CUnseenForce(float top,float left,float width,float height);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};