#pragma once
#include "GameObject.h"
#define HEARTICON_BBOX_WIDTH 16
#define HEARTICON_BBOX_HEIGHT 26
enum class HeartIconAnim {
	IDLE=900
};
class CHeartIcon : public CGameObject
{
public:
	CHeartIcon() { prevAnim = currentAnim = (int)HeartIconAnim::IDLE; state = GAMEOBJECT_STATE_VISIBLE; }
};

