#pragma once
#include "Timer.h"
#define DEFAULT_FREEZE_TIME 1000
class CTimeFreezer {
	CTimer timer;
	static CTimeFreezer* __instance;
public:
	void Active(DWORD time = DEFAULT_FREEZE_TIME) { OutputDebugString(L"Freezer Active"); timer.SetTime(time); timer.Active(); }
	bool isActive();
	bool isOn() { return timer.isActive(); }
	static CTimeFreezer* GetInstance();
};
