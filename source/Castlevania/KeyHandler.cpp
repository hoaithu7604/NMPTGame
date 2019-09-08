#pragma once
#include "KeyHandler.h"
#include <dinput.h>
#include "Game.h"
#include "Simon.h"

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
	if (CGame::GetInstance()->IsKeyDown(DIK_Z)) {
		CSimon::GetInstance()->DoAction(Action::ATTACK);
	}
	else if (CGame::GetInstance()->IsKeyDown(DIK_DOWN)) {
		CSimon::GetInstance()->DoAction(Action::CROUCH);
	}
	else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT)) 
	{
		CSimon::GetInstance()->DoAction(Action::WALK_LEFT);
	}
	else if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {
		CSimon::GetInstance()->DoAction(Action::WALK_RIGHT);
	}
	else {
		CSimon::GetInstance()->DoAction(Action::IDLE);
	}
}