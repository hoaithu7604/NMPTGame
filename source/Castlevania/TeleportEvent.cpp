#include "TeleportEvent.h"
#include "Simon.h"
#include "Debug.h"
bool CTeleportEvent::ShouldTrigger()
{
	return isTriggering || isContaining(CSimon::GetInstance());
}
void CTeleportEvent::Trigger()
{
	CSimon*simon = CSimon::GetInstance();
	simon->SetPosition(targetX, targetY);
	isTriggering = false;
}