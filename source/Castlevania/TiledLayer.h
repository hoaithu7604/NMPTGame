#pragma once
#include <string>
#include <vector>
#include "TiledObject.h"
#define TILED_LAYER_TYPE_TILELAYER "tilelayer"
#define TILED_LAYER_TYPE_OBJECTGROUP "objectgroup"

using namespace std;

/*
	class for Tiled Layer object
*/
class CTiledLayer {
	int id;

	vector<int> data; //tilelayer only
	vector<LPTILEDOBJECT> objects; // objectgroup only

	string name;
	string type;
	int height;
	int width;

	//there are still more fields but i dont have anything to do with them now
};
typedef CTiledLayer* LPTILEDLAYER