#include "TiledObject.h"
#include "Simon.h"
#include "UnseenForce.h"

CTiledObject::CTiledObject(json root)
{
	id = root[TILED_OBJECT_ID].get<int>();
	name = root[TILED_OBJECT_NAME].get<string>();
	rotation = root[TILED_OBJECT_ROTATION].get<float>();
	x = root[TILED_OBJECT_X].get<float>();
	y = root[TILED_OBJECT_Y].get<float>();
	width = root[TILED_OBJECT_WIDTH].get<int>();
	height = root[TILED_OBJECT_HEIGHT].get<int>();
	json propertiesRoot = root[TILED_OBJECT_PROPERTIES];
	for (json::iterator it = propertiesRoot.begin(); it != propertiesRoot.end(); it++)
	{
		json propertyRoot = *it;
		string propertyName = propertyRoot[TILED_OBJECT_PROPERTY_NAME];
		string propertyType = propertyRoot[TILED_OBJECT_PROPERTY_TYPE];
		string propertyValue = propertyRoot[TILED_OBJECT_PROPERTY_VALUE];
		CTiledProperty*property = new CTiledProperty(propertyName, propertyType, propertyValue);
		properties.push_back(property);
	}
}
void CTiledObject::Create()
{
	if (name==OBJECTCODE_SIMON)
	{
		CSimon* simon = CSimon::GetInstance();
		simon->SetPosition(x, y);		
	}
	else if (name == OBJECTCODE_CAMERABOUND)
	{
		CCamera::GetInstance()->AddCameraBound(x, y, x + width, y + height);
	}
	else if (name == OBJECTCODE_UNSEENFORCE)
	{
		CUnseenForce* obj = new CUnseenForce(x, y, width, height);
		CGameObject::AddObject(obj);
	}
}