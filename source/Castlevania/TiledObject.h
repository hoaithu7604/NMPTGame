#pragma once
#include <string>
#include <vector>
#include <nlohmann\json.hpp>
#define TILED_PROPERTY_STAIR_TYPE "stairtype"
#define TILED_PROPERTY_STAIR_TYPE_UP "up"
#define TILED_PROPERTY_STAIR_TYPE_DOWN "down"
#define TILED_PROPERTY_ITEMHOLDER "itemholder"
#define TILED_PROPERTY_BRICK_TYPE "bricktype"
#define TILED_PROPERTY_TARGET_POS_X "target_pos_x"
#define TILED_PROPERTY_TARGET_POS_Y "target_pos_y"
#define DOOREVENT_CAMERAX "cameraX"
#define DOOREVENT_CAMERAY "cameraY"
#define DOOREVENT_DOORX "doorX"
#define DOOREVENT_DOORY "doorY"
#define DOOREVENT_TARGETX "targetX"
#define DOOREVENT_TARGETY "targetY"
#define DOOREVENT_FINISHX "finishX"
#define DOOREVENT_FINISHY "finishY"
#define BATEVENT_BATX "batX"
#define BATEVENT_BATY "batY"
#define BATEVENT_CAMERAX "cameraX"
#define BATEVENT_CAMERAY "cameraY"
#define TILED_OBJECT_PROPERTY_NAME "name"
#define TILED_OBJECT_PROPERTY_TYPE "type"
#define TILED_OBJECT_PROPERTY_VALUE "value"
#define TILED_OBJECT_NAME "name"
#define TILED_OBJECT_ID "id"
#define TILED_OBJECT_PROPERTIES "properties"
#define TILED_OBJECT_ROTATION "rotation"
#define TILED_OBJECT_X "x"
#define TILED_OBJECT_Y "y"
#define TILED_OBJECT_WIDTH "width"
#define TILED_OBJECT_HEIGHT "height"
#define OBJECTCODE_SIMON "simon"
#define OBJECTCODE_CAMERABOUND "camerabound"
#define OBJECTCODE_UNSEENFORCE "unseenforce"
#define OBJECTCODE_SIMONROPE "simonrope"
#define OBJECTCODE_TORCH "torch"
#define OBJECTCODE_FLAME_EFFECT "flameeffect"
#define OBJECTCODE_BIGHEART "bigheart"
#define OBJECTCODE_ROPEITEM "ropeitem"
#define OBJECTCODE_HEALTHICON "healthicon"
#define OBJECTCODE_ITEMFRAME "itemframe"
#define OBJECTCODE_HEARTICON "hearticon"
#define OBJECTCODE_DAGGER "dagger"
#define OBJECTCODE_FIREBOMB "firebomb"
#define OBJECTCODE_AUTOWALKEVENT "autowalkevent"
#define OBJECTCODE_TELEPORTEVENT "teleportevent"
#define OBJECTCODE_CANDLE "candle"
#define OBJECTCODE_TINYHEART "tinyheart"
#define OBJECTCODE_ZOMBIESPAWNER "zombiespawner"
#define OBJECTCODE_ZOMBIE "zombie"
#define OBJECTCODE_STAIRS "stairs"
#define OBJECTCODE_HOUND "hound"
#define OBJECTCODE_HOUNDSPAWNER "houndspawner"
#define OBJECTCODE_MONEYBAG "moneybag"
#define OBJECTCODE_CROSS_FLAME_EFFECT "crossflameeffect"
#define OBJECTCODE_IMBRICK "imbrick"
#define OBJECTCODE_BRICK_BREAKING_EFFECT "brickbreakingeffect"
#define OBJECTCODE_CROSS "cross"
#define OBJECTCODE_GATE "gate"
#define OBJECTCODE_DOOREVENT "doorevent"
#define OBJECTCODE_BAT "bat"
#define OBJECTCODE_BATSPAWNER "batspawner"
#define OBJECTCODE_FISH "fish"
#define OBJECTCODE_FISHSPAWNER "fishspawner"
#define OBJECTCODE_FIREBALL "fireball"
#define OBJECTCODE_ITEMSPAWNEVENT "itemspawnevent"
#define OBJECTCODE_PORKCHOP "porkchop"
#define OBJECTCODE_WATCH "watch"
#define OBJECTCODE_MEDICINEJAR "medicinejar"
#define OBJECTCODE_AXE "axe"
#define OBJECTCODE_NIRENSYA "nirensya"
#define OBJECTCODE_VAMPIREBATEVENT "vampirebatevent"
#define OBJECTCODE_VAMPIREBAT "vampirebat"
#define OBJECTCODE_MAGICCRYSTAL "magiccrystal"
using json = nlohmann::json;
using namespace std;
/*
class for Tiled Object
*/
struct CTiledProperty {
	string name;
	string type;
	string value_string;
	float value_float;
	CTiledProperty(string name, string type, string value_string)
		:name(name), type(type), value_string(value_string) {}
	CTiledProperty(string name, string type, float value_float)
		:name(name), type(type), value_float(value_float) {}
};
typedef CTiledProperty* LPTILEDPROPERTY;
class CTiledObject {
	int id;
	string name;
	vector<LPTILEDPROPERTY> properties;
	float rotation;
	float x;
	float y;
	int width;
	int height;
public:
	CTiledObject(json root);
	void Create();
};
typedef CTiledObject* LPTILEDOBJECT;