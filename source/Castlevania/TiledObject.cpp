#pragma once
#include "TiledObject.h"
#include "Simon.h"
#include "UnseenForce.h"
#include "Torch.h"
#include "AutoWalkEvent.h"
#include "TeleportEvent.h"
#include "Candle.h"
#include "ZombieSpawner.h"
#include "Stairs.h"
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
		if (propertyRoot[TILED_OBJECT_PROPERTY_VALUE].is_number_float())
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

}