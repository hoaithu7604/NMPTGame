#include "Weapon.h"
bool CWeapon::isOnCooldown()
{
	return cooldown_timer.isActive() && !cooldown_timer.hasTicked();
}