#include "Entity.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Game.h"
#include "Player.h"


Entity::Entity(const char* path, SDL_Renderer* renderer, int x, int y) : renderer(renderer)
{
	destRectangle.x = x;
	destRectangle.y = y;

	srcRectangle.h = 0;
	srcRectangle.w = 0;
	srcRectangle.x = 0;
	srcRectangle.y = 0;

	texture = TextureManager::LoadTexture(path, renderer);
}

Entity::~Entity()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	renderer = nullptr;

};

void Entity::init() {

	srcRectangle.h = 0;
	srcRectangle.w = 0;
	srcRectangle.x = 0;
	srcRectangle.y = 0;

	destRectangle.w = 0;
	destRectangle.h = 0;

	move.setPositionx(destRectangle.x);
	move.setPositiony(destRectangle.y);

}

void Entity::update()
{
	move.update();

	destRectangle.x = static_cast<int>(move.getPositionx() - Game::camera.x);
	destRectangle.y = static_cast<int>(move.getPositiony() - Game::camera.y);

}

void Entity::draw()
{
	SDL_RenderCopyEx(renderer, texture, &srcRectangle, &destRectangle, NULL, NULL, SDL_FLIP_NONE);
}

SDL_Rect Entity::getdestRect()
{
	return this->destRectangle;
}

