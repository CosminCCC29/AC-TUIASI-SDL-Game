#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Vector2D.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y) : renderer(renderer)
{
	srcRectangle.x = 0;
	srcRectangle.y = 0;
	srcRectangle.w = 0;
	srcRectangle.h = 0;

	position.x = destRectangle.x = x;
	position.y = destRectangle.y = y;

	texture = TextureManager::LoadTexture(textureSheet, renderer);
}

GameObject::~GameObject() = default;

void GameObject::init() {

	srcRectangle.h = 60;
	srcRectangle.w = 40;
	srcRectangle.x = 0;
	srcRectangle.y = 0;

	destRectangle.w = 40;
	destRectangle.h = 60;

}

void GameObject::update()
{
	destRectangle.x = static_cast<int>(position.x - Game::camera.x);
	destRectangle.y = static_cast<int>(position.y - Game::camera.y);
}

void GameObject::draw()
{
	SDL_RenderCopy(renderer, texture, &srcRectangle, &destRectangle);
}

SDL_Rect GameObject::getdestRect()
{
	return this->destRectangle;
}