#pragma once
#include "TiledObject.h"
#include "Simon.h"
#include "UnseenForce.h"
#include "Torch.h"
#include "AutoWalkEvent.h"
#include "TeleportEvent.h"
#include "ItemSpawnEvent.h"
#include "Candle.h"
#include "Stairs.h"
#include "ZombieSpawner.h"
#include "HoundSpawner.h"
#include "ImBrick.h"
#include "DoorEvent.h"
#include "BatSpawner.h"
#include "FishSpawner.h"
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
		string propertyName = propertyRoot[TILED_OBJECT_PROPERTY_NAME].get<string>();
		string propertyType = propertyRoot[TILED_OBJECT_PROPERTY_TYPE].get<string>();
		if (propertyRoot[TILED_OBJECT_PROPERTY_VALUE].is_number())
		{
			float propertyValue = propertyRoot[TILED_OBJECT_PROPERTY_VALUE].get<float>();
			CTiledProperty*property = new CTiledProperty(propertyName, propertyType, propertyValue);
			properties.push_back(property);
		}
		else if (propertyRoot[TILED_OBJECT_PROPERTY_VALUE].is_string())
		{
			string propertyValue = propertyRoot[TILED_OBJECT_PROPERTY_VALUE].get<string>();
			CTiledProperty*property = new CTiledProperty(propertyName, propertyType, propertyValue);
			properties.push_back(property);
		}
		
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
	else if (name == OBJECTCODE_TORCH)
	{
		CTorch*obj = new CTorch();
		obj->SetPosition(x, y);
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name==TILED_PROPERTY_ITEMHOLDER)
			{
				obj->AddItem(properties[i]->value_string);
			}
		}
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_AUTOWALKEVENT)
	{
		CAutoWalkEvent*obj = new CAutoWalkEvent(x,y,width,height);
		float pos_x, pos_y;
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == TILED_PROPERTY_TARGET_POS_X)
			{
				pos_x = properties[i]->value_float;
			}
			else if (properties[i]->name == TILED_PROPERTY_TARGET_POS_Y)
			{
				pos_y = properties[i]->value_float;
			}
		}
		obj->SetTargetPos(pos_x, pos_y);
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_TELEPORTEVENT) 
	{
		CTeleportEvent*obj = new CTeleportEvent(x, y, width, height);
		float pos_x, pos_y;
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == TILED_PROPERTY_TARGET_POS_X)
			{
				pos_x = properties[i]->value_float;
			}
			else if (properties[i]->name == TILED_PROPERTY_TARGET_POS_Y)
			{
				pos_y = properties[i]->value_float;
			}
		}
		obj->SetTargetPos(pos_x, pos_y);
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_ITEMSPAWNEVENT)
	{
		CItemSpawnEvent*obj = new CItemSpawnEvent(x, y, width, height);
		float pos_x, pos_y;
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == TILED_PROPERTY_TARGET_POS_X)
			{
				pos_x = properties[i]->value_float;
			}
			else if (properties[i]->name == TILED_PROPERTY_TARGET_POS_Y)
			{
				pos_y = properties[i]->value_float;
			}
		}
		obj->SetTargetPos(pos_x, pos_y);
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_CANDLE)
	{
		CCandle*obj = new CCandle();
		obj->SetPosition(x, y);
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == TILED_PROPERTY_ITEMHOLDER)
			{
				obj->AddItem(properties[i]->value_string);
			}
		}
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_ZOMBIESPAWNER)
	{
		CZombieSpawner*obj = new CZombieSpawner(x, y, width, height);
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_STAIRS)
	{
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == TILED_PROPERTY_STAIR_TYPE)
			{
				if (properties[i]->value_string == TILED_PROPERTY_STAIR_TYPE_UP)
				{
					CGameObject::AddObject(new CStairs(x,y+height,x+width,y));
				}
				else if (properties[i]->value_string == TILED_PROPERTY_STAIR_TYPE_DOWN)
				{
					CGameObject::AddObject(new CStairs(x, y, x + width, y+height));
				}
			}
		}
	}
	else if (name == OBJECTCODE_HOUNDSPAWNER)
	{
		CHoundSpawner*obj = new CHoundSpawner(x, y, width, height);
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_IMBRICK)
	{
		CImBrick*obj = new CImBrick(x, y);
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == TILED_PROPERTY_ITEMHOLDER)
			{
				obj->AddItem(properties[i]->value_string);
			}
			else if (properties[i]->name == TILED_PROPERTY_BRICK_TYPE)
			{
				obj->SetType(properties[i]->value_float);
			}
		}
		CGameObject::AddObject(obj);
	}
	else if (name == OBJECTCODE_DOOREVENT)
	{
		float cameraX, cameraY, doorX, doorY, targetX, targetY, finishX, finishY;
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties[i]->name == DOOREVENT_CAMERAX)
			{
				cameraX = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_CAMERAY)
			{
				cameraY = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_DOORX)
			{
				doorX = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_DOORY)
			{
				doorY = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_TARGETX)
			{
				targetX = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_TARGETY)
			{
				targetY = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_FINISHX)
			{
				finishX = properties[i]->value_float;
			}
			else if (properties[i]->name == DOOREVENT_FINISHY)
			{
				finishY = properties[i]->value_float;
			}
		}
		CGameObject::AddObject(new CDoorEvent(x, y, width, height, cameraX, cameraY, doorX, doorY, targetX, targetY, finishX, finishY));
	}
	else if (name == OBJECTCODE_BATSPAWNER)
	{
		CGameObject::AddObject(new CBatSpawner(x, y, width, height));
	}
	else if (name == OBJECTCODE_FISHSPAWNER)
	{
		CGameObject::AddObject(new CFishSpawner(x, y, width, height));
	}
}