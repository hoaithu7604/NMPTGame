#pragma once
#include "GameObject.h"

vector<LPGAMEOBJECT> * CGameObject::objects = NULL;
CGameObject::CGameObject()
{
	nx = 1;
	argb = CARGB();
	animations = CAnimations::GetInstance();	
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
}
bool CGameObject::isOnCamera() {
	CCamera*camera = CCamera::GetInstance();
	float left, top, right, bottom;
	camera->GetViewSize(top, left, bottom, right);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	//true only when this object completely on camera
	return left <= l && top <= t && right >= r && bottom >= b;
}
bool CGameObject::isAlmostOnCamera() {
	CCamera*camera = CCamera::GetInstance();
	float left, top, right, bottom;
	camera->GetViewSize(top, left, bottom, right);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	// true if this object overlapping camera view
	return l < right && r > left && t < bottom && b > top;
}
int CGameObject::isBarelyOffscreen()
{
	CCamera*camera = CCamera::GetInstance();
	float left, top, right, bottom;
	camera->GetViewSize(top, left, bottom, right);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	// if this object is offscreen but not that far 
	if (t >= top && b <= bottom)
	{
		if (l > left - BARELY_OFFSCREEN_DISTANCE && l < left)
		{
			return DIRECTION_LEFT; //left side
		}
		else if (r > right&&r < right + BARELY_OFFSCREEN_DISTANCE)
		{
			return DIRECTION_RIGHT; // right side
		}
	}
	else if (l >= left&&r <= right)
	{
		if (b > bottom&& b < bottom + BARELY_OFFSCREEN_DISTANCE)
		{
			return DIRECTION_DOWN;
		}
	}
	else return 0; //it's far offscreen or onscreen
}
bool CGameObject::isFarOffscreen()
{
	CCamera*camera = CCamera::GetInstance();
	float left, top, right, bottom;
	camera->GetViewSize(top, left, bottom, right);
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);
	return r<left-BARELY_OFFSCREEN_DISTANCE||l>right+ BARELY_OFFSCREEN_DISTANCE||b<top-BARELY_OFFSCREEN_DISTANCE||t>bottom+BARELY_OFFSCREEN_DISTANCE;
}
void CGameObject::Render() {
	if (!state.IsRenderable()) return;
	//if (currentAnim == -1) return; //this object doesn't have animations, may delete later because update state
	if (prevAnim != currentAnim) {
		animations->Get(prevAnim)->Reset(); // reset previous animation if object's animation get changed
		prevAnim = currentAnim;
	}
	animations->Get(currentAnim)->Render(x, y, argb);
	//RenderBoundingBox();
}
void CGameObject::RenderOverlay() {
	if (!state.IsRenderable()) return;
	if (currentAnim == -1) return; //this object doesn't have animations
	if (prevAnim != currentAnim) {
		animations->Get(prevAnim)->Reset(); // reset previous animation if object's animation get changed
		prevAnim = currentAnim;
	}
	animations->Get(currentAnim)->RenderOverlay(x, y, argb);
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
void CGameObject::TakeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		health = 0;
		Destroy();
	}
}
void CGameObject::FreezeAnimation()
{
	if (currentAnim != -1&&state.IsRenderable())
	{
		animations->Get(currentAnim)->ResetCurrentFrameTime();
	}
}
bool CGameObject::isOverlapping(CGameObject*obj)
{
	float left, top, right, bottom;
	obj->GetBoundingBox(left, top, right, bottom);
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	return l < right && r > left && t < bottom && b > top;
}
float CGameObject::Distance(CGameObject*obj)
{
	return sqrt((x - obj->x)*(x - obj->x) + (y - obj->y)*(y - obj->y));
}
bool CGameObject::isContaining(CGameObject*obj)
{
	float left, top, right, bottom;
	obj->GetBoundingBox(left, top, right, bottom);
	float l, t, r, b;
	this->GetBoundingBox(l, t, r, b);
	return l <= left && t <= top && r >= right && b >= bottom;
}
void CGameObject::GetCentralPoint(float &x, float&y)
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	x = (left + right) / 2;
	y = (top + bottom) / 2;
};
void CGameObject::SetPositionCentral(float x, float y)
{
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	this->x = x - (right - left) / 2;
	this->y = y - (bottom-top) / 2;
}
void CGameObject::RenderBoundingBox()
{
	if (!state.IsColliable()||!state.IsRenderable()) return;
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