#pragma once
#include "GameObject.h"


CGameObject::CGameObject()
{
	animations = CAnimations::GetInstance();
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t=0, nx=0, ny=0;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;


	GetBoundingBox(ml, mt, mr, mb);

	

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}
wchar_t *string2wchar_t1(const string &str) // fix later too tired now .-.
{
	wchar_t wchar[260];
	int index = 0;
	while (index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

void CGameObject::LoadResource(string ObjectName)
{
	wstring ws_ObjectName;
	ws_ObjectName.assign(ObjectName.begin(), ObjectName.end());
	wstring filePath = wstring(OBJECTDATA_PATH) + ws_ObjectName + L".dat";

	ifstream inputFile(filePath.c_str());
	string data = "";
	string sign = "";
	while (inputFile >> data)
	{
		if (data == "EOF")
			break;
		if ((sign == ""||sign!=data) && (data == "SPRITEDATA" || data == "ANIMATIONDATA")) sign = data;
		if (sign == "SPRITEDATA")
		{
			inputFile >> data;
			int texture_id = atoi(data.c_str());
			while (inputFile >> data)
			{
				if (data == "SPRITEDATAEND") 
					break;		
				int sprite_id = atoi(data.c_str());
				int left, top, right, bottom;
				inputFile >> data;
				left = atoi(data.c_str());
				inputFile >> data;
				top = atoi(data.c_str());
				inputFile >> data;
				right = atoi(data.c_str());
				inputFile >> data;
				bottom = atoi(data.c_str());
				CSprites::GetInstance()->Add(sprite_id, left, top, right, bottom, CTextures::GetInstance()->Get(texture_id));
			}
		}
		if (sign == "ANIMATIONDATA")
		{
			int previous_anim_id = -1;
			int anim_id;
			LPANIMATION anim = NULL;
			while (inputFile >> data)
			{

				if (data == "ANIMATIONDATAEND") break;
				anim_id = atoi(data.c_str());
				if (previous_anim_id != anim_id)
				{
					if (anim != NULL)
					{
						//will make some changes here later: changing animations to pointer or just removing Animations Manager class
						CAnimations::GetInstance()->Add(previous_anim_id, anim);
						
					}
					previous_anim_id = anim_id;
					anim = new CAnimation(100);
				}
				inputFile >> data;
				int sprite_id = atoi(data.c_str());
				inputFile >> data;
				DWORD frametime = atoi(data.c_str());
				anim->Add(sprite_id, frametime);
				

			}
		}
	}

}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}



CGameObject::~CGameObject()
{

}