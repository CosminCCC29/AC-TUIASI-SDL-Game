#pragma once
#include <SDL.h>
#include "Movement.h"

class Component
{
public:
	virtual ~Component() = default;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void drawUpdate() = 0;

	virtual SDL_Rect getdestRect() = 0;

};