#pragma once
#include <d3dx9.h>
/*
	class for Tiled Tile objects
*/
class CTiledTile {

	int id; 

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;

};
typedef CTiledTile * LPTILEDTILE;