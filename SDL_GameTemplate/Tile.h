#pragma once

#include <SDL.h>
#include "Movement.h"
#include "TextureManager.h"

class Tile : public Component
{
	SDL_Renderer* renderer;
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

	float scale;

	int tileID;



public:
	Movement move;

	Tile();
	Tile(int id, SDL_Renderer* renderer);

	void init();
	void update();
	void draw();
	void drawUpdate();
	SDL_Rect getdestRect();

};