#pragma once
#include "AnimationFrame.h"
class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation();
	CAnimation(int defaultTime);
	void Add(int spriteId, DWORD time = 0);
	void Reset();
	void Render(float x, float y, int alpha = 255);
};

typedef CAnimation *LPANIMATION;
