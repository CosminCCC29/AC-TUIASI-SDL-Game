#pragma once
#include <SDL.h>
#include "Component.h"
#include "Lives.h"
#include "Collision.h"
#include "Player.h"
#include "GameObject.h"
#include "Game.h"
#include "Entity.h"
#include "Projectile.h"
#include "Zombie.h"

#include <cstdlib> 
#include <ctime>

Lives::Lives()
{
	for (int i = 0; i < 50; ++i)
	{
		this->flag[i] = false;
	}

	lives = 0;

	texture = nullptr;
	renderer = nullptr;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 0;
	destRect.h = 0;

}

Lives::Lives(const char* path, SDL_Renderer* renderer) : renderer(renderer)
{
	lives = 0;

	for (int i = 0; i < 50; ++i)
	{
		this->flag[i] = false;
	}

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 0;
	srcRect.h = 0;

	destRect.x = 0;	
	destRect.y = 0;
	destRect.w = 0;
	destRect.h = 0;

	texture = TextureManager::LoadTexture(path, renderer);
}

void Lives::init()
{

	lives = 3;

	for (unsigned int i = 0; i < Game::getEnemyMaxNumber(); ++i)
	{
		flag[i] = true;
	}

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 320;
	srcRect.h = 64;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 320;
	destRect.h = 64;
}

void Lives::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer, SDL_FLIP_NONE);
}

void Lives::drawUpdate()
{
	switch (Lives::lives)
	{
	case 3:
		srcRect.y = 0;
		break;

	case 2:
		srcRect.y = 64;
		break;

	case 1:
		srcRect.y = 128;
		break;

	case 0:
		srcRect.y = 192;
		break;

	default:
		srcRect.y = 192;
		break;
	}
}

void Lives::update()
{
	drawUpdate();
}

SDL_Rect Lives::getdestRect()
{
	return this->destRect;
}

