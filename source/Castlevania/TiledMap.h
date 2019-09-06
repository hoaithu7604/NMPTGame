#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "TiledLayer.h"
#include "TiledTileset.h"
using namespace std;

/*
	class for Tiled Map object
*/
class CTiledMap {
	int height; //Number of tile rows
	int width; // Number of tile columns
	int nextlayerid; //Auto-increments for each layer
	int nextobjectid; // Auto-increments for each layer
	int tileheight;
	int tilewidth;
	//
	vector<LPTILEDLAYER> layers;
	LPTILEDTILESET tileset; // should be vector 
	//fields that we should ignore for now
	bool infinite; //Whether the map has infinite dimensions
	string orientation; 
	string renderorder;
	string tiledversion;
	string type;
	float version;
public:
	//CTiledMap(LPCWSTR jsonPath);
};