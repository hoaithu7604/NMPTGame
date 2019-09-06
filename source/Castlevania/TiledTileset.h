#pragma once
#include <string>
#include <vector>
#include "TiledTile.h"
using namespace std;
/*
	class for Tiled Tileset object
*/
class CTiledTileset {
	string source; //dir to Tileset json
	int firstgid; //GID corresponding to the first tile in the set
	int columns; //The number of tile columns in the tileset
	
	int imagewidth;
	int imageheight;
	int tilecount;
	int tileheight;
	int tilewidth;
	 
	vector<LPTILEDTILE> tiles; 

	//fields that i should ignore for now
	int margin; // Buffer between image edge and first tile (pixels)
	string type;
	string image; // to be converted to interger (id in database), but for now lets just load texture id 0
	string tiledversion;
	float version;
};
typedef CTiledTileset* LPTILEDTILESET;