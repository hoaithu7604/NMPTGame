#include "TimeFreezer.h"
CTimeFreezer* CTimeFreezer::__instance = NULL;
CTimeFreezer* CTimeFreezer::GetInstance()
{
	if (__instance == NULL) __instance = new CTimeFreezer();
	return __instance;
}
bool CTimeFreezer::isActive()
{
	if (timer.isActive()&& !timer.hasTicked())
	{
		return true;
	}
	return false;
}