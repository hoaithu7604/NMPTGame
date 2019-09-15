#pragma once
#include "KeyHandler.h"
#include <dinput.h>
#include "Game.h"
#include "Simon.h"

void CKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	if(KeyCode == DIK_Z) {
		if ((CGame::GetInstance()->IsKeyDown(DIK_UP)&&CSimon::GetInstance()->CanUseWeapon()))
			CSimon::GetInstance()->DoAction(Action::USE_WEAPON);
		else
		CSimon::GetInstance()->DoAction(Action::ATTACK);
	}
	else if (KeyCode == DIK_X) {
		CSimon::GetInstance()->DoAction(Action::JUMP);
	}
	else if (KeyCode == DIK_C)
	{
		CSimon::GetInstance()->SetPosition(5224,581);
	}
	else if (KeyCode == DIK_A)
	{
		float x, y;
		CSimon::GetInstance()->GetPosition(x, y);
		CSimon::GetInstance()->SetPosition(x, y-100);
	}
	else if (KeyCode == DIK_1)
	{
		CSimon::GetInstance()->SetPosition(3052, 216);
	}
	else if (KeyCode == DIK_2)
	{
		CSimon::GetInstance()->SetPosition(4590, 135);
	}
	else if (KeyCode == DIK_3)
	{
		CSimon::GetInstance()->SetPosition(5348, 170);
	}
	else if (KeyCode == DIK_4)
	{
		CSimon::GetInstance()->SetPosition(6062, 163);
	}
	else if (KeyCode == DIK_5)
	{
		CSimon::GetInstance()->SetPosition(7050, 281);
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
		CSimon::GetInstance()->DoAction(Action::GO_DOWN_STAIRS);
		should_simon_do_nothing = false;
	}
	else
	{
		if (CGame::GetInstance()->IsKeyDown(DIK_UP))
		{
			CSimon::GetInstance()->DoAction(Action::GO_UP_STAIRS);
		}
		if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		{
			CSimon::GetInstance()->DoAction(Action::WALK_LEFT);
			CSimon::GetInstance()->DoAction(Action::GO_STAIRS_LEFT);
			should_simon_do_nothing = false;
		}
		if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT)) {
			CSimon::GetInstance()->DoAction(Action::WALK_RIGHT);
			CSimon::GetInstance()->DoAction(Action::GO_STAIRS_RIGHT);
			should_simon_do_nothing = false;
		}
	}
	if (should_simon_do_nothing)
		CSimon::GetInstance()->DoAction(Action::IDLE);

}