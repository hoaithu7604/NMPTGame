#include "Zombie.h"

CZombie::CZombie()
	:CMonster()
{
	currentAnim = prevAnim = (int)ZombieAnimID::LEFT;
	point = ZOMBIE_POINT;
}
CZombie::CZombie(float x, float y, float nx)
	:CMonster()
{
	SetPositionCentral(x, y);
	vx = nx > 0 ? ZOMBIE_WALKING_SPEED : -ZOMBIE_WALKING_SPEED;
	currentAnim = prevAnim = nx > 0 ? (int)ZombieAnimID::RIGHT: (int)ZombieAnimID::LEFT;
	point = ZOMBIE_POINT;
}
void CZombie::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x; 
	top = y; 
	right = left + ZOMBIE_BBOX_WIDTH; 
	bottom =top+ZOMBIE_BBOX_HEIGHT; 
}

