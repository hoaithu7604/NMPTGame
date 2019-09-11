#include "Timer.h"
#include "string"
using namespace std;
bool CTimer::hasTicked()
{
	if (start == DEFAULT_TIME) return false; //not on
	DWORD now = GetTickCount();
	if (now - start >= time)
	{
		start = DEFAULT_TIME;
		return true;
	}
	return false;
}