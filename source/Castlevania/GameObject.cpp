#pragma once
#include "GameObject.h"

vector<LPGAMEOBJECT> * CGameObject::objects = NULL;
CGameObject::CGameObject()
{
	animations = CAnimations::GetInstance();	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}
void CGameObject::Render() {
	if (state != GAMEOBJECT_STATE_VISIBLE&&state!= GAMEOBJECT_STATE_ACTIVE) return;
	if (currentAnim == -1) return; //this object doesn't have animations
	if (prevAnim != currentAnim) {
		animations->Get(prevAnim)->Reset(); // reset previous animation if object's animation get changed
		prevAnim = currentAnim;
	}
	animations->Get(currentAnim)->Render(x, y, 255);
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

				if (data == "ANIMATIONDATAEND")
				{
					if (anim!=NULL) CAnimations::GetInstance()->Add(previous_anim_id, anim);
					break;
				}
				anim_id = atoi(data.c_str());
				if (previous_anim_id != anim_id)
				{
					if (anim != NULL)
					{
						
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

	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 100);
}



CGameObject::~CGameObject()
{

}