#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Collision
{

public:

	static bool AABB(const SDL_Rect& a, const SDL_Rect& b)
	{
		if ((a.x + a.w >= b.x) && (b.x + b.w >= a.x) && (a.y + a.h >= b.y) && (b.y + b.h >= a.y))
			return 1;
		else
			return 0;
	}

	static bool Left(const SDL_Rect& a, const SDL_Rect& b)
	{
		if (a.x + a.w >= b.x)
			return 1;
		else
			return 0;
	}

	static bool Right(const SDL_Rect& a, const SDL_Rect& b)
	{
		if (b.x + b.w >= a.x)
			return 1;
		else
			return 0;
	}

	static bool Down(const SDL_Rect& a, const SDL_Rect& b)
	{
		if (a.y + a.h >= b.y)
			return 1;
		else
			return 0;
	}

	static bool Up(const SDL_Rect& a, const SDL_Rect& b)
	{
		if (b.y + b.h >= a.y)
			return 1;
		else
			return 0;
	}

};