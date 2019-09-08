#include "Torch.h"
void CTorch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + TORCH_BBOX_WIDTH;
	bottom = top + TORCH_BBOX_HEIGHT;
}