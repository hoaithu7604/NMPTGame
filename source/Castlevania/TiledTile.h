#pragma once
#include <d3dx9.h>
/*
	class for Tiled Tile objects
*/
class CTiledTile {

	//int id; nothing to do with it for now 

	int left;
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public:
	CTiledTile(int left, int top, int right, int bottom, int texture_id);
	void Draw(float x, float y, int alpha = 255);
};
typedef CTiledTile * LPTILEDTILE;