#pragma once
#include "AnimationFrame.h"
#include "ARGB.h"
class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation();
	CAnimation(int defaultTime);
	void ResetCurrentFrameTime();
	int GetCurrentFrame() { return currentFrame; }
	int GetFramesCount() { return frames.size(); }
	bool isLastFrame() { return currentFrame == frames.size() - 1; }
	bool isFirstFrame() { return currentFrame == 0; }
	void Add(int spriteId, DWORD time = 0);
	void Reset();
	void Render(float x, float y, CARGB argb = CARGB());
	void RenderOverlay(float x, float y, CARGB argb = CARGB());
};

typedef CAnimation *LPANIMATION;
