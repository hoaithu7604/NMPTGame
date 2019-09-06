#pragma once
#include <string>
#include <vector>
#define TILED_PROPERTY_ITEMHOLDER "itemholder"
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
class CTiledObject {
	int id;
	string name;
	vector<CTiledProperty> properties;
	float rotation;
	float x;
	float y;
	float width;
	float height;
};
typedef CTiledObject* LPTILEDOBJECT