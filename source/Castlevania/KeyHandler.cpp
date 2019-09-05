#pragma once
#include "KeyHandler.h"

void CKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

}

void CKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CKeyHandler::KeyState(BYTE *states)
{

}