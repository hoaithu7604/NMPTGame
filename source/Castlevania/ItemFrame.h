#pragma once
#include "GameObject.h"
#define ITEMFRAME_BBOX_WIDTH 64
#define ITEMFRAME_BBOX_HEIGHT 44
enum class ItemFrameAnim {
	IDLE=800
};
class CItemFrame : public CGameObject
{

public:
	CItemFrame() { prevAnim = currentAnim = (int)ItemFrameAnim::IDLE; state = GAMEOBJECT_STATE_VISIBLE; }
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};