#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Game.h"
#include "Simon.h"
#include "HealthIcon.h"
#define OVERLAYBOARD_DEFAULT_POINT 0
#define OVERLAYBOARD_TIME 280 // (second)
#define TICK_PER_SECOND 1000
#define OVERLAYBOARD_POINT_X 0
#define OVERLAYBOARD_POINT_Y 0
#define OVERLAYBOARD_POINT_DIGITS_COUNT 6
#define OVERLAYBOARD_POINT_TEXT "SCORE-"
#define OVERLAYBOARD_TIMER_X OVERLAYBOARD_POINT_X + 200
#define OVERLAYBOARD_TIMER_Y OVERLAYBOARD_POINT_Y 
#define OVERLAYBOARD_TIMER_DIGITS_COUNT 4
#define OVERLAYBOARD_TIMER_TEXT "TIME "
#define OVERLAYBOARD_STAGE_X OVERLAYBOARD_TIMER_X + 160
#define OVERLAYBOARD_STAGE_Y OVERLAYBOARD_POINT_Y 
#define OVERLAYBOARD_STAGE_DIGITS_COUNT 2
#define OVERLAYBOARD_STAGE_TEXT "STAGE "
#define OVERLAYBOARD_PLAYER_HEALTH_X OVERLAYBOARD_POINT_X
#define OVERLAYBOARD_PLAYER_HEALTH_Y OVERLAYBOARD_POINT_Y + 50
#define OVERLAYBOARD_PLAYER_HEALTH_TEXT "PLAYER "
#define OVERLAYBOARD_PLAYER_HEALTH_ICON_Y 50
#define OVERLAYBOARD_PLAYER_HEALTH_SPACING 2

class COverlayBoard:CGameObject {
	int point;
	int stage;
	CTimer timer;
	// make life easier
	CGame* game; 
	CSimon* simon;
	vector<CHealthIcon*> playerHealth;
	vector<CHealthIcon*> enemyHealth;
	//----
	static COverlayBoard* __instance;
public:
	COverlayBoard();

	void IncreasePoint(int point) { this->point += point; }


	static COverlayBoard * GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
};