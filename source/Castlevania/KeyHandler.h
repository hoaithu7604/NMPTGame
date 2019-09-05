#pragma once
#include "Debug.h"
#include <Windows.h>
class CKeyHandler 
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

typedef CKeyHandler * LPKEYHANDLER;