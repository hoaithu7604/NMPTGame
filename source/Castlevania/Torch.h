#pragma once
#include "ItemHolder.h"
#define TORCH_BBOX_HEIGHT 64
#define TORCH_BBOX_WIDTH 32
enum class TorchAnimID {
	IDLE = 300
};
class CTorch : public CItemHolder {
public:
	CTorch() :CItemHolder() { currentAnim = (int)TorchAnimID::IDLE; prevAnim = (int)TorchAnimID::IDLE; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};