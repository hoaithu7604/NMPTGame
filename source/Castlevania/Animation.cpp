#pragma once
#include "Animation.h"

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}
void CAnimation::Reset()
{
	currentFrame = -1;
}
CAnimation::CAnimation()
{
	lastFrameTime = -1;
	currentFrame = -1;
}

CAnimation::CAnimation(int defaultTime)
{
	this->defaultTime = defaultTime;
	lastFrameTime = -1;
	currentFrame = -1;
}
void CAnimation::ResetCurrentFrameTime() {
	if (currentFrame != -1)
	{
		lastFrameTime = GetTickCount();
	}
}
void CAnimation::Render(float x, float y, CARGB argb)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
		frames[currentFrame]->GetSprite()->Draw(x, y, argb);
	}
	else
	{
		frames[currentFrame]->GetSprite()->Draw(x, y, argb);

		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
}
void CAnimation::RenderOverlay(float x, float y, CARGB argb)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
		frames[currentFrame]->GetSprite()->DrawOverlay(x, y, argb);
	}
	else
	{
		frames[currentFrame]->GetSprite()->DrawOverlay(x, y, argb);

		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
}
