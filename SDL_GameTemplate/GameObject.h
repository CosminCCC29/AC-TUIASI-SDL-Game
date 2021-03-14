#pragma once
#include "SDL_image.h"
#include "Component.h"
#include "Collision.h"

class GameObject : public Component
{
public:
	GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	~GameObject();

	void init();
	void update();
	void drawUpdate() {};
	void draw();

	SDL_Rect getdestRect() override;

private:
	SDL_Rect destRectangle;
	SDL_Rect srcRectangle;
	Vector2D position;

	SDL_Texture* texture;
	SDL_Renderer* renderer;
};