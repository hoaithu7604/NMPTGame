#pragma once
#include "Maps.h"

CMaps* CMaps::__instance = NULL;
CMaps* CMaps::GetInstance() {
	if (__instance == NULL)
		__instance = new CMaps();
	return __instance;
};
