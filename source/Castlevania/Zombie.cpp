#include "Zombie.h"

CZombie::CZombie()
	:CMonster(ZOMBIE_POINT, ZOMBIE_HEALTH_DEFAULT)
{
	currentAnim = prevAnim = (int)ZombieAnimID::LEFT;
	contactDamage = ZOMBIE_CONTACT_DAMAGE;
}
CZombie::CZombie(float x, float y, float nx)
	:CMonster(ZOMBIE_POINT, ZOMBIE_HEALTH_DEFAULT)
{
	SetPositionCentral(x, y);
	vx = nx > 0 ? ZOMBIE_WALKING_SPEED : -ZOMBIE_WALKING_SPEED;
	currentAnim = prevAnim = nx > 0 ? (int)ZombieAnimID::RIGHT: (int)ZombieAnimID::LEFT;
	contactDamage = ZOMBIE_CONTACT_DAMAGE;
}
void CZombie::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = x; 
	top = y; 
	right = left + ZOMBIE_BBOX_WIDTH; 
	bottom =top+ZOMBIE_BBOX_HEIGHT; 
}

