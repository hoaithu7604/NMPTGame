#include "MoneyBag.h"

CMoneyBag::CMoneyBag(float x, float y, int tier)
	:CItemObject()
{
	this->x = x - MONEYBAG_BBOX_WIDTH / 2;
	this->y = y - MONEYBAG_BBOX_HEIGHT / 2;
	switch (tier) {
	case MONEYBAG_TIER_ONE:
		prevAnim = currentAnim = (int)MoneyBagAnimID::TIER_ONE;
		point = MONEYBAG_TIER_ONE_POINT;
		break;
	case MONEYBAG_TIER_TWO:
		prevAnim = currentAnim = (int)MoneyBagAnimID::TIER_TWO;
		point = MONEYBAG_TIER_TWO_POINT;
		break;
	case MONEYBAG_TIER_THREE:
		prevAnim = currentAnim = (int)MoneyBagAnimID::TIER_THREE;
		point = MONEYBAG_TIER_THREE_POINT;
		break;
	case MONEYBAG_TIER_FOUR:
		prevAnim = currentAnim = (int)MoneyBagAnimID::TIER_FOUR;
		point = MONEYBAG_TIER_FOUR_POINT;
		break;
	}
}
void CMoneyBag::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + MONEYBAG_BBOX_WIDTH;
	bottom = top + MONEYBAG_BBOX_HEIGHT;
}