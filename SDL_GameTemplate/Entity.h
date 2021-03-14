#pragma once
#include "SDL_image.h"
#include "Component.h"
#include "Movement.h"

class Entity : public Component
{
public:
	Entity(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	~Entity();

	void init();
	void update();
	void drawUpdate() {};
	void draw();

	SDL_Rect getdestRect() override;

	Movement move;
protected:
	SDL_Rect srcRectangle;
	SDL_Rect destRectangle;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
};
