#pragma once
#include "ItemHolder.h"
#define TORCH_BBOX_HEIGHT 64
#define TORCH_BBOX_WIDTH 32
#define TORCH_HEALTH_DEFAULT 1
enum class TorchAnimID {
	IDLE = 300
};
class CTorch : public CItemHolder {
public:
	CTorch() :CItemHolder() { health = TORCH_HEALTH_DEFAULT; currentAnim = (int)TorchAnimID::IDLE; prevAnim = (int)TorchAnimID::IDLE; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};