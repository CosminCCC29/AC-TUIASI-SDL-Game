#include "Tile.h"
#include "Game.h"
#include "Player.h"


Tile::Tile() : tileID(0), renderer(nullptr), texture(nullptr)
{
	scale = 1;

	destRect.x = 0;	srcRect.x = 0;
	destRect.y = 0; srcRect.y = 0;
	destRect.w = 0; srcRect.w = 0;
	destRect.h = 0; srcRect.h = 0;
}

Tile::Tile(int id, SDL_Renderer* renderer) : tileID(id), renderer(renderer)
{
	destRect.x = 0;	srcRect.x = 0;
	destRect.y = 0; srcRect.y = 0;
	destRect.w = 0; srcRect.w = 0;
	destRect.h = 0; srcRect.h = 0;

	switch (tileID)
	{

	case 1:
		texture = TextureManager::LoadTexture("assets/map/1.bmp", renderer);
		break;

	case 5:
		texture = TextureManager::LoadTexture("assets/map/5.bmp", renderer);
		break;

	case 9:
		texture = TextureManager::LoadTexture("assets/map/9.bmp", renderer);
		break;

	case 18:
		texture = TextureManager::LoadTexture("assets/map/18.bmp", renderer);
		break;

	case 22:
		texture = TextureManager::LoadTexture("assets/map/22.bmp", renderer);
		break;

	case 49:
		texture = TextureManager::LoadTexture("assets/map/49.bmp", renderer);
		break;

	case 51:
		texture = TextureManager::LoadTexture("assets/map/51.bmp", renderer);
		break;

	case 53:
		texture = TextureManager::LoadTexture("assets/map/53.bmp", renderer);
		break;

	case 57:
		texture = TextureManager::LoadTexture("assets/map/57.bmp", renderer);
		break;

	case 58:
		texture = TextureManager::LoadTexture("assets/map/58.bmp", renderer);
		break;

	case 59:
		texture = TextureManager::LoadTexture("assets/map/59.bmp", renderer);
		break;

	case 60:
		texture = TextureManager::LoadTexture("assets/map/60.bmp", renderer);
		break;

	case 63:
		texture = TextureManager::LoadTexture("assets/map/63.bmp", renderer);
		break;

	case 64:
		texture = TextureManager::LoadTexture("assets/map/64.bmp", renderer);
		break;

	default:
		texture = TextureManager::LoadTexture("assets/dirt.png", renderer);
		break;

	}
}

void Tile::init()
{
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 64;
	srcRect.h = 64;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 64;
	destRect.h = 64;

	move.setPositionx(destRect.x);
	move.setPositiony(destRect.y);
}

void Tile::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer, SDL_FLIP_NONE);
}

void Tile::drawUpdate()
{

}

void Tile::update()
{
	destRect.x = static_cast<int>(move.getPositionx());
	destRect.y = static_cast<int>(move.getPositiony());
}

SDL_Rect Tile::getdestRect()
{
	return this->destRect;
}