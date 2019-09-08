#include "SimonRope.h"
#include "Simon.h"
#include "Torch.h"
CSimonRope::CSimonRope()
	:CGameObject()
{
	state = GAMEOBJECT_STATE_ACTIVE;
	level = SIMON_ROPE_LEVEL_DEFAULT;
	currentAnim = (int)RopeAnimID::LEVEL_ONE_LEFT;
	prevAnim = (int)RopeAnimID::LEVEL_ONE_LEFT;
	
}
void CSimonRope::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x;
	bottom = y;
	if (animations->Get(currentAnim)->isLastFrame())
	{
		switch (level) 
		{
		case SIMON_ROPE_LEVEL_ONE:
			right += SIMON_ROPE_LEVEL_ONE_LAST_FRAME_BBOX_WIDTH;
			bottom += SIMON_ROPE_LEVEL_ONE_LAST_FRAME_BBOX_HEIGHT;
			break;
		case SIMON_ROPE_LEVEL_TWO:
			right += SIMON_ROPE_LEVEL_TWO_LAST_FRAME_BBOX_WIDTH;
			bottom += SIMON_ROPE_LEVEL_TWO_LAST_FRAME_BBOX_HEIGHT;
			break;
		case SIMON_ROPE_LEVEL_THREE:
			right += SIMON_ROPE_LEVEL_THREE_LAST_FRAME_BBOX_WIDTH;
			bottom += SIMON_ROPE_LEVEL_THREE_LAST_FRAME_BBOX_HEIGHT;
			break;
		}
		
	}
}
void CSimonRope::Update(float x,float y, DWORD nx,DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// update only it's actived
	if (!_isActive) return;
	
	this->x = x;
	this->y = y;
	this->nx = nx;
	

	UpdateCurrentAnim();
	UpdatePosition();

	if (animations->Get(currentAnim)->isLastFrame()) {
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (isOverlapping(coObjects->at(i)))
			{
				if (dynamic_cast<CTorch*>(coObjects->at(i)))
				{
					dynamic_cast<CTorch*>(coObjects->at(i))->Destroy();
				}
			}
		}
	}
}
void CSimonRope::Render()
{
	// render only if it's actived
	if (!_isActive) return;
	CGameObject::Render();
}
void CSimonRope::UpdateCurrentAnim()
{
	if (this->level == SIMON_ROPE_LEVEL_ONE) {
		currentAnim = nx > 0 ? (int)RopeAnimID::LEVEL_ONE_RIGHT : (int)RopeAnimID::LEVEL_ONE_LEFT;
	}
	else if (this->level == SIMON_ROPE_LEVEL_TWO) {
		currentAnim = nx > 0 ? (int)RopeAnimID::LEVEL_TWO_RIGHT : (int)RopeAnimID::LEVEL_TWO_LEFT;
	} 
	else if (this->level == SIMON_ROPE_LEVEL_THREE) {
		currentAnim = nx > 0 ? (int)RopeAnimID::LEVEL_THREE_RIGHT : (int)RopeAnimID::LEVEL_THREE_LEFT;
	}
}
void CSimonRope::UpdatePosition()
{
	int ropeLastFrameBBoxWidth;
	switch (level)
	{
	case SIMON_ROPE_LEVEL_ONE:
		ropeLastFrameBBoxWidth = SIMON_ROPE_LEVEL_ONE_LAST_FRAME_BBOX_WIDTH;
		break;
	case SIMON_ROPE_LEVEL_TWO:
		ropeLastFrameBBoxWidth = SIMON_ROPE_LEVEL_TWO_LAST_FRAME_BBOX_WIDTH;
		break;
	case SIMON_ROPE_LEVEL_THREE:
		ropeLastFrameBBoxWidth = SIMON_ROPE_LEVEL_THREE_LAST_FRAME_BBOX_WIDTH;
		break;
	}
	LPANIMATION currentAnim = animations->Get(this->currentAnim);

	if (currentAnim->isLastFrame()) 
	{
		isFirstFrame = false;
		x = nx > 0 ? x + SIMON_IDLE_BBOX_WIDTH : x - ropeLastFrameBBoxWidth;
		y = y + SIMON_ROPE_LAST_FRAME_ADJUSTING_Y;
	}
	else
	{
		x = nx > 0 ? x - SIMON_ROPE_TWO_FIRST_FRAME_BBOX_WIDTH : x + SIMON_IDLE_BBOX_WIDTH;
		if (!isFirstFrame&&currentAnim->isFirstFrame()) 
		{
			currentAnim->Reset();
			_isActive = false;
		}
	}
}
