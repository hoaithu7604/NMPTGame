#include "CrossEffect.h"
#include "Monster.h"

void CCrossEffect::Render()
{
	if (!state.IsRenderable()) return;
	if (changeBG)
	{
		CGame * game = CGame::GetInstance();
		LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
		LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
		LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
		d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(255,255,255,255));
		changeBG = false;
	}
	else changeBG = true;
}
void CCrossEffect::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (timer.hasTicked())
	{
		state = GAMEOBJECT_STATE_INVISIBLE;
	}
	else
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CMonster*>(obj)&&obj->isOnCamera()) // only affect onscreen monster
				obj->TakeDamage(CROSS_EFFECT_DAMAGE);
		}
	}
}