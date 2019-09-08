#pragma once
#include "KeyHandler.h"
#include <dinput.h>
#include "Game.h"
#include "Simon.h"

void CKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if(KeyCode == DIK_Z) {
		CSimon::GetInstance()->DoAction(Action::ATTACK);
	}
	else if (KeyCode == DIK_X) {
		CSimon::GetInstance()->DoAction(Action::JUMP);
	}
	
}

void CKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	
	
}
void CKeyHandler::KeyState(BYTE *states)
{
	bool should_simon_do_nothing = true;
	if (CGame::GetInstance()->IsKeyDown(DIK_DOWN)) {
		CSimon::GetInstance()->DoAction(Action::CROUCH);
		should_simon_do_nothing = false;
	}
	else
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			CSimon::GetInstance()->DoAction(Action::WALK_LEFT);
			should_simon_do_nothing = false;
		}
		if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {
			CSimon::GetInstance()->DoAction(Action::WALK_RIGHT);
			should_simon_do_nothing = false;
		}
	}
	if (should_simon_do_nothing)
		CSimon::GetInstance()->DoAction(Action::IDLE);

}