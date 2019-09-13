#pragma once
#include "ItemHolder.h"
#define IMBRICK_HEALTH_DEFAULT 1;
#define IMBRICK_BBOX_WIDTH 32
#define IMBRICK_BBOX_HEIGHT 30
#define IMBRICK_TYPE_ONE 1
#define IMBRICK_TYPE_TWO 2
#define EFFECT_COUNT 3
enum class ImBrickAnimID {
	TYPEONE = 1700,
	TYPETWO
};
class CImBrick : public CItemHolder
{
	
public:
	CImBrick(float x,float y);
	void SetType(float type);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(); //this thing should be rendered even it's not fully onscreen
	virtual void Destroy(); //this thing has different effect
};