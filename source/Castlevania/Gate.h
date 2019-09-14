#pragma once
#include "GameObject.h"
#define GATE_BBOX_WIDTH 16
#define GATE_BBOX_HEIGHT 96
enum class GateAnimID
{
	IDLE = 2100,
	OPEN,
	CLOSE,
};
class CGate : public CGameObject
{
public:
	CGate() { state = GAMEOBJECT_STATE_VISIBLE; prevAnim = currentAnim = (int)GateAnimID::IDLE; }
	virtual void Render() { if (isOnCamera()) CGameObject::Render(); }
	void Open() { currentAnim = (int)GateAnimID::OPEN; }
	void Close() { currentAnim = (int)GateAnimID::CLOSE; }
};