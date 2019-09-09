#pragma once
#include "Sprite.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}


void CSprite::Draw(float x, float y, CARGB argb)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, argb);
}
void CSprite::DrawOverlay(float x, float y, CARGB argb)
{
	CGame * game = CGame::GetInstance();
	game->DrawOverlay(x, y, texture, left, top, right, bottom, argb);
}
