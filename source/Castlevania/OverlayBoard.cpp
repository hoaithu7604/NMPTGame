#include "OverlayBoard.h"

COverlayBoard* COverlayBoard::__instance = NULL;
COverlayBoard * COverlayBoard::GetInstance()
{
	if (__instance == NULL) __instance = new COverlayBoard();
	return __instance;
}
COverlayBoard::COverlayBoard()
{
	state = GAMEOBJECT_STATE_VISIBLE;
	x = y = 10;
	stage = 3; //lets not care about this now
	point = OVERLAYBOARD_DEFAULT_POINT;
	timer.SetTime(OVERLAYBOARD_TIME*TICK_PER_SECOND);
	timer.Active();
	game = CGame::GetInstance();
	simon = CSimon::GetInstance();
	weapon = simon->GetWeapon();
	itemframe = new CItemFrame();
	itemframe->SetPosition(x + OVERLAYBOARD_ITEM_FRAME_X, y + OVERLAYBOARD_ITEM_FRAME_Y);
	heart = new CHeartIcon();
	heart->SetPosition(x + OVERLAYBOARD_HEART_X, y + OVERLAYBOARD_HEART_Y);
	for (int i = 0; i < SIMON_HEALTH_DEFAULT; i++)
	{
		int pos_x = x + OVERLAYBOARD_PLAYER_HEALTH_X + OVERLAYBOARD_PLAYER_HEALTH_ICON_Y
			+OVERLAYBOARD_PLAYER_HEALTH_SPACING*i+HEALTHICON_BBOX_WIDTH*i;
		int pos_y = y + OVERLAYBOARD_PLAYER_HEALTH_Y;
		CHealthIcon*icon = new CHealthIcon();
		icon->SetPosition(pos_x, pos_y);
		icon->SetAnimation((int)HealthIconAnim::PLAYER);
		playerHealth.push_back(icon);
	}
	for (int i = 0; i < SIMON_HEALTH_DEFAULT; i++)
	{
		int pos_x = x + OVERLAYBOARD_ENEMY_HEALTH_X + OVERLAYBOARD_ENEMY_HEALTH_ICON_Y
			+ OVERLAYBOARD_ENEMY_HEALTH_SPACING * i + HEALTHICON_BBOX_WIDTH * i;
		int pos_y = y + OVERLAYBOARD_ENEMY_HEALTH_Y;
		CHealthIcon*icon = new CHealthIcon();
		icon->SetPosition(pos_x, pos_y);
		icon->SetAnimation((int)HealthIconAnim::ENEMY);
		enemyHealth.push_back(icon);
	}
}
void COverlayBoard::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (timer.hasTicked())
	{
		//game over here
	}
	else 
	{
		weapon = simon->GetWeapon();
		if (weapon != NULL)
		{
			float x, y;
			itemframe->GetCentralPoint(x, y);
			weapon->SetPositionCentral(x, y);
		}
		int currentHealth = simon->GetHealth();
		for (int i = 0; i < SIMON_HEALTH_DEFAULT; i++) 
		{
			if (i < currentHealth)
				playerHealth[i]->SetAnimation((int)HealthIconAnim::PLAYER);
			else
				playerHealth[i]->SetAnimation((int)HealthIconAnim::EMPTY);
		}
		int enemyCurrentHealth = 8; // update current enemy health here
		for (int i = 0; i < ENEMY_HEALTH_DEFAULT; i++)
		{
			if (i < enemyCurrentHealth)
				enemyHealth[i]->SetAnimation((int)HealthIconAnim::ENEMY);
			else
				enemyHealth[i]->SetAnimation((int)HealthIconAnim::EMPTY);
		}
	}
}
void COverlayBoard::Render()
{
	//point
	string pointString = to_string(point);
	pointString.insert(pointString.begin(), OVERLAYBOARD_POINT_DIGITS_COUNT - pointString.size(), '0');
	pointString = OVERLAYBOARD_POINT_TEXT + pointString;
	game->DrawString(x+OVERLAYBOARD_POINT_X, y+OVERLAYBOARD_POINT_Y, pointString);
	//timer
	int time = timer.GetRemainingTime() / TICK_PER_SECOND;
	string timerString = to_string(time);
	timerString.insert(timerString.begin(), OVERLAYBOARD_TIMER_DIGITS_COUNT - timerString.size(), '0');
	timerString = OVERLAYBOARD_TIMER_TEXT + timerString;
	game->DrawString(x + OVERLAYBOARD_TIMER_X, y + OVERLAYBOARD_TIMER_Y, timerString);
	//stage
	string stageString = to_string(stage);
	stageString.insert(stageString.begin(), OVERLAYBOARD_STAGE_DIGITS_COUNT - stageString.size(), '0');
	stageString = OVERLAYBOARD_STAGE_TEXT + stageString;
	game->DrawString(x + OVERLAYBOARD_STAGE_X, y + OVERLAYBOARD_STAGE_Y, stageString);
	//player health
	string playerHealthString = OVERLAYBOARD_PLAYER_HEALTH_TEXT;
	game->DrawString(x + OVERLAYBOARD_PLAYER_HEALTH_X, y + OVERLAYBOARD_PLAYER_HEALTH_Y, playerHealthString);
	for (int i = 0; i < SIMON_HEALTH_DEFAULT; i++)
	{
		playerHealth[i]->RenderOverlay();
	}
	//enemy health
	string enemyHealthString = OVERLAYBOARD_ENEMY_HEALTH_TEXT;
	game->DrawString(x + OVERLAYBOARD_ENEMY_HEALTH_X, y + OVERLAYBOARD_ENEMY_HEALTH_Y, enemyHealthString);
	for (int i = 0; i < ENEMY_HEALTH_DEFAULT; i++)
	{
		enemyHealth[i]->RenderOverlay();
	}
	//item frame
	itemframe->RenderOverlay();
	//render item here later;
	if (weapon!=NULL) weapon->RenderOverlay();

	//heart
	heart->RenderOverlay();
	int heartCount = simon->GetHeart();
	string heartString = to_string(heartCount);
	heartString.insert(heartString.begin(), OVERLAYBOARD_HEART_DIGITS_COUNT - heartString.size(), '0');
	heartString = OVERLAYBOARD_HEART_TEXT + heartString;
	game->DrawString(x + OVERLAYBOARD_HEART_TEXT_X, y + OVERLAYBOARD_HEART_TEXT_Y, heartString);
	//playcount
	string playcountString = to_string(3); // fix later maybe, just maybe
	playcountString.insert(playcountString.begin(), OVERLAYBOARD_PLAY_COUNT_DIGITS_COUNT - playcountString.size(), '0');
	playcountString = OVERLAYBOARD_PLAY_COUNT_TEXT + playcountString;
	game->DrawString(x + OVERLAYBOARD_PLAY_COUNT_X, y + OVERLAYBOARD_PLAY_COUNT_Y, playcountString);
}