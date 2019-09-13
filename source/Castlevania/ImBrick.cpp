#include "ImBrick.h"
#include "BrickBreakingEffect.h"
void CImBrick::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + IMBRICK_BBOX_WIDTH;
	bottom = top + IMBRICK_BBOX_HEIGHT;
}
CImBrick::CImBrick(float x, float y)
	:CItemHolder()
{
	this->x = x;
	this->y = y;
}
void CImBrick::SetType(float type)
{
	switch ((int)type) {
	case IMBRICK_TYPE_ONE:
		prevAnim = currentAnim = (int)ImBrickAnimID::TYPEONE;
		break;
	case IMBRICK_TYPE_TWO:
		prevAnim = currentAnim = (int)ImBrickAnimID::TYPETWO;
		break;
	}
}
void CImBrick::Render()
{
	if (isOnCamera() || isAlmostOnCamera())
		CGameObject::Render();
}
void CImBrick::Destroy()
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	float pos_x = (left + right) / 2;
	float pos_y = (top + bottom) / 2;
	for (int i = 0; i < EFFECT_COUNT; i++)
		CBrickBreakingEffect*effect = new CBrickBreakingEffect(pos_x, pos_y);
	delay_timer.Active();
	state = GAMEOBJECT_STATE_UPDATE_ONLY;
}