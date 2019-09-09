#pragma once
#include <Windows.h>
#define DEFAULT_TIME 0
#define DEFAULT_TIME_VALUE 1000
using namespace std;
class CTimer
{
	DWORD start;
	DWORD time;
public:
	CTimer() { time = DEFAULT_TIME_VALUE; }
	CTimer(DWORD time) { this->time = time; start = DEFAULT_TIME; }
	void SetTime(DWORD time) { this->time = time; }
	void Reset() { this->start = DEFAULT_TIME; }
	bool isActive() { return start != DEFAULT_TIME; }
	void Active() { this->start = GetTickCount(); }
	bool hasTicked();
	DWORD GetRemainingTime() { return time - (GetTickCount() - start); }
};