#pragma once
#include "Timer.h"
#define DEFAULT_FREEZE_TIME 1000
class CTimeFreezer {
	CTimer timer;
	static CTimeFreezer* __instance;
	bool ShouldSimon;
public:
	void Active(DWORD time = DEFAULT_FREEZE_TIME, bool ShouldSimon = true) { OutputDebugString(L"Freezer Active"); timer.SetTime(time); timer.Active(); this->ShouldSimon = ShouldSimon; }
	bool isActive();
	bool ShouldSimonFreeze() { return ShouldSimon; }
	bool isOn() { return timer.isActive(); }
	static CTimeFreezer* GetInstance();
};
