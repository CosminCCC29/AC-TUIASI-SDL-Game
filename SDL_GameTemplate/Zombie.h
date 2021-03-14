#pragma once
#include "SDL_image.h"
#include "Component.h"
#include "Movement.h"
#include "Entity.h"


class Zombie : public Entity
{
public:

	Zombie(const char* textureSheet, SDL_Renderer* renderer, int x, int y);
	~Zombie();

	void init();
	void update();
	void drawUpdate() {};
	void draw();

	void setAngle(float ang);
	void followUpdate();

	SDL_Rect getdestRect();

private:
	float angle;
};
