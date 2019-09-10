#include "ItemFrame.h"

void CItemFrame::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{ 
	left = x;
	top = y; 
	right = left + ITEMFRAME_BBOX_WIDTH; 
	bottom = top + ITEMFRAME_BBOX_HEIGHT; 
};