#pragma once
#include <SDL_image.h>
#include "Tile.h"
#include <iostream>

class Map
{
public:
	Map(SDL_Renderer* renderer);
	~Map();

	void LoadMap(const char * file);
	void DrawTiles(int xpos, int ypos);
	void update();

private:

	Tile* Tiles[100];
	unsigned int mapScale;
	SDL_Renderer* renderer;

	int map[23][45];

};