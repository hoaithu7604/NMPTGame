#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Game.h"
#include "Simon.h"
#include "HealthIcon.h"
#include "ItemFrame.h"
#include "HeartIcon.h"
#define OVERLAYBOARD_LINE_SPACING 15
#define OVERLAYBOARD_DEFAULT_POINT 0
#define OVERLAYBOARD_TIME 300 // (second)
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
#define OVERLAYBOARD_PLAYER_HEALTH_Y OVERLAYBOARD_POINT_Y + OVERLAYBOARD_LINE_SPACING
#define OVERLAYBOARD_PLAYER_HEALTH_TEXT "PLAYER "
#define OVERLAYBOARD_PLAYER_HEALTH_ICON_Y 100
#define OVERLAYBOARD_PLAYER_HEALTH_SPACING 0
#define OVERLAYBOARD_ENEMY_HEALTH_X OVERLAYBOARD_POINT_X
#define OVERLAYBOARD_ENEMY_HEALTH_Y OVERLAYBOARD_PLAYER_HEALTH_Y + OVERLAYBOARD_LINE_SPACING
#define OVERLAYBOARD_ENEMY_HEALTH_TEXT "ENEMY "
#define OVERLAYBOARD_ENEMY_HEALTH_ICON_Y 100
#define OVERLAYBOARD_ENEMY_HEALTH_SPACING 0
#define OVERLAYBOARD_ITEM_FRAME_X OVERLAYBOARD_PLAYER_HEALTH_ICON_Y+OVERLAYBOARD_ENEMY_HEALTH_SPACING*(SIMON_HEALTH_DEFAULT-1)+HEALTHICON_BBOX_WIDTH*SIMON_HEALTH_DEFAULT+10
#define OVERLAYBOARD_ITEM_FRAME_Y OVERLAYBOARD_PLAYER_HEALTH_Y
#define OVERLAYBOARD_HEART_X OVERLAYBOARD_ITEM_FRAME_X + ITEMFRAME_BBOX_WIDTH + 10
#define OVERLAYBOARD_HEART_Y OVERLAYBOARD_PLAYER_HEALTH_Y 
#define OVERLAYBOARD_HEART_DIGITS_COUNT 2
#define OVERLAYBOARD_HEART_TEXT "-"
#define OVERLAYBOARD_HEART_TEXT_X OVERLAYBOARD_HEART_X+HEARTICON_BBOX_WIDTH+1
#define OVERLAYBOARD_HEART_TEXT_Y OVERLAYBOARD_HEART_Y
#define OVERLAYBOARD_PLAY_COUNT_X OVERLAYBOARD_HEART_X
#define OVERLAYBOARD_PLAY_COUNT_Y OVERLAYBOARD_ENEMY_HEALTH_Y + 3
#define OVERLAYBOARD_PLAY_COUNT_DIGITS_COUNT 2
#define OVERLAYBOARD_PLAY_COUNT_TEXT "P-"

#define ENEMY_HEALTH_DEFAULT 16 // delete later

class COverlayBoard:CGameObject {
	int point;
	int stage;
	CTimer timer;
	// make life easier
	CGame* game; 
	CSimon* simon;
	CItemFrame* itemframe;
	CHeartIcon* heart;
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