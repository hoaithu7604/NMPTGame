#pragma once
#include "GameObject.h"
class CUnseenForce : public CGameObject 
{
	float width;
	float height;
	float bottom;
	float right;
public:
	CUnseenForce(float x,float y,float width,float height);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render() { CGameObject::Render(); CGameObject::RenderBoundingBox(); };
};