#pragma once
#include "GameObject.h"
class CUnseenWater : public CGameObject
{
	float width;
	float height;
	float bottom;
	float right;
public:
	CUnseenWater(float x, float y, float width, float height);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render() { CGameObject::Render(); CGameObject::RenderBoundingBox(); };
};