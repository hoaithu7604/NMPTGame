/* =============================================================
	
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "KeyHandler.h"
#include "Textures.h"
#include "Simon.h"
#include "Camera.h"
#include "Maps.h"
#include "SimonRope.h"
#include "Torch.h"
#include "FlameEffect.h"
#include "BigHeart.h"
#include "TimeFreezer.h"
#include "RopeItem.h"
#include "OverlayBoard.h"
#include "ItemFrame.h"
#include "HeartIcon.h"
//weapon
#include "Dagger.h"
#include "FireBomb.h"

#include "Candle.h"
#include "TinyHeart.h"
#include "Zombie.h"
#include "Hound.h"
#include "MoneyBag.h"
#include "CrossFlameEffect.h"
#include "ImBrick.h"
#include "BrickBreakingEffect.h"
#include "Cross.h"
#include "Gate.h"
#include "Bat.h"
#include "Fish.h"
#include "FireBall.h"
#include "PorkChop.h"
#include "Watch.h"
#include "MedicineJar.h"
#include "Axe.h"
#include "Nirensya.h"
#include "VampireBat.h"
#include "MagicCrystal.h"
#include "EventObject.h"
#include "BubbleEffect.h"
#include "Grid.h"
#include "Boomerang.h"
#include "PointEffect.h"
#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 525 //~13
#define SCREEN_HEIGHT 460
#define CAMERA_WIDTH 512
#define CAMERA_HEIGH 416
#define MAX_FRAME_RATE 120
#define MAP_TO_THE_BAT_PATH L"Resource\\Stages\\ToTheBat.json"
CGame *game;
CGrid* grid;

vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> activeObjects;

CSimon * simon;
CKeyHandler * keyHandler; 
CTextures * texture;
CSprites * sprites;
CAnimations * animations;
CCamera * camera;
CMaps * maps;
CTimeFreezer* freezer; // if this timer is on, no update, render only, freeze objects animation
COverlayBoard* board;
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void Init()
{
	simon = CSimon::GetInstance();
}
void LoadResources()
{
	CGameObject::Init(&objects); 
	freezer = CTimeFreezer::GetInstance();
	texture = CTextures::GetInstance();
	sprites = CSprites::GetInstance();
	animations = CAnimations::GetInstance();
	camera = CCamera::GetInstance();
	camera->SetSize(CAMERA_WIDTH, CAMERA_HEIGH);
	camera->SetMode(CAMERA_MODE_INSTANT);
	camera->SetType(CAMERA_TYPE_FOLLOW);
	texture->LoadResource();

	CSimon::LoadResource(OBJECTCODE_SIMON);
	CSimonRope::LoadResource(OBJECTCODE_SIMONROPE);
	CTorch::LoadResource(OBJECTCODE_TORCH);
	CFlameEffect::LoadResource(OBJECTCODE_FLAME_EFFECT);
	CBigHeart::LoadResource(OBJECTCODE_BIGHEART);
	CRopeItem::LoadResource(OBJECTCODE_ROPEITEM);
	CHealthIcon::LoadResource(OBJECTCODE_HEALTHICON);
	CItemFrame::LoadResource(OBJECTCODE_ITEMFRAME);
	CHeartIcon::LoadResource(OBJECTCODE_HEARTICON);
	CDagger::LoadResource(OBJECTCODE_DAGGER);
	CFireBomb::LoadResource(OBJECTCODE_FIREBOMB);
	CCandle::LoadResource(OBJECTCODE_CANDLE);
	CTinyHeart::LoadResource(OBJECTCODE_TINYHEART);
	CZombie::LoadResource(OBJECTCODE_ZOMBIE);
	CHound::LoadResource(OBJECTCODE_HOUND);
	CMoneyBag::LoadResource(OBJECTCODE_MONEYBAG);
	CCrossFlameEffect::LoadResource(OBJECTCODE_CROSS_FLAME_EFFECT);
	CImBrick::LoadResource(OBJECTCODE_IMBRICK);
	CBrickBreakingEffect::LoadResource(OBJECTCODE_BRICK_BREAKING_EFFECT);
	CCross::LoadResource(OBJECTCODE_CROSS);
	CGate::LoadResource(OBJECTCODE_GATE);
	CBat::LoadResource(OBJECTCODE_BAT);
	CFish::LoadResource(OBJECTCODE_FISH);
	CFireBall::LoadResource(OBJECTCODE_FIREBALL);
	CPorkChop::LoadResource(OBJECTCODE_PORKCHOP);
	CWatch::LoadResource(OBJECTCODE_WATCH);
	CMedicineJar::LoadResource(OBJECTCODE_MEDICINEJAR);
	CAxe::LoadResource(OBJECTCODE_AXE);
	CNirensya::LoadResource(OBJECTCODE_NIRENSYA);
	CVampireBat::LoadResource(OBJECTCODE_VAMPIREBAT);
	CMagicCrystal::LoadResource(OBJECTCODE_MAGICCRYSTAL);
	CBubbleEffect::LoadResource(OBJECTCODE_BUBBLEEFFECT);
	CBoomerang::LoadResource(OBJECTCODE_BOOMERANG);
	CPointEffect::LoadResource(OBJECTCODE_POINTEFFECT);
	//
	board = COverlayBoard::GetInstance();
	maps = CMaps::GetInstance();
	LPTILEDMAP map = new CTiledMap(MAP_TO_THE_BAT_PATH);
	maps->Add(map);
	grid = new CGrid(maps->GetCurrentMap()->getMapWidth(), maps->GetCurrentMap()->GetMapHeight());
	CGrid::SetInstance(grid);
	maps->GetCurrentMap()->CreateObject();
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	activeObjects.clear();
	float left, top, right, bottom;
	camera->GetViewSize(top, left, bottom, right);
	grid->UpdateActiveCells(left,top,right,bottom);
	grid->UpdateActiveObjects();
	
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> upObjects;
	upObjects.push_back(simon);
	
	grid->GetActiveObjects(activeObjects);
	//add active objects
	for (int i = 0; i < activeObjects.size(); i++)
	{
		if (activeObjects.at(i)->IsUpdatable())
			upObjects.push_back(activeObjects.at(i));
		if (activeObjects.at(i)->IsColliable())
			coObjects.push_back(activeObjects.at(i));
	}
	//add event objects
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects.at(i)->IsUpdatable())
			upObjects.push_back(objects.at(i));
		if (objects.at(i)->IsColliable())
			coObjects.push_back(objects.at(i));
	}
	if (freezer->isActive()) {
		if (freezer->ShouldSimonFreeze()) 
		{
			simon->FreezeAnimation();
		}
		else simon->Update(dt,&coObjects);
		for (int i = 0; i < activeObjects.size(); i++)
			activeObjects[i]->FreezeAnimation();
	}
	else 
	{
		for (int i = 0; i < upObjects.size(); i++)
			upObjects[i]->Update(dt, &coObjects);
	}
	board->Update(dt);
	camera->Update(dt);

	grid->UpdateCells();
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		//render
		maps->GetCurrentMap()->Draw();		
		for (int i = 0; i < activeObjects.size(); i++)
		{
			activeObjects[i]->Render();
		}
		simon->Render();
		board->Render();
		//
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	Init();
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CKeyHandler();
	game->InitKeyboard(keyHandler);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*1.5, SCREEN_HEIGHT*1.5, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}