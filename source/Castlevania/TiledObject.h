#pragma once
#include <string>
#include <vector>
#include <nlohmann\json.hpp>
#define TILED_PROPERTY_ITEMHOLDER "itemholder"
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
using json = nlohmann::json;
using namespace std;
/*
class for Tiled Object
*/
struct CTiledProperty {
	string name;
	string type;
	string value;
	CTiledProperty(string name, string type, string value) 
		:name(name), type(type), value(value){}
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