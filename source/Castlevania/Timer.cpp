#include "Timer.h"
#include "string"
using namespace std;
bool CTimer::hasTicked()
{
	DWORD now = GetTickCount();
	if (now - start >= time)
	{
		start = DEFAULT_TIME;
		return true;
	}
	return false;
}