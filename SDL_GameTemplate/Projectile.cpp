#include "Projectile.h"
#include "Player.h"
#include "Entity.h"
#include "Game.h"
#include "Zombie.h"

int Projectile::counter;

Projectile::Projectile(int speed, int xpos, int ypos, SDL_Renderer* renderer) : speed(speed), renderer(renderer)
{
	SDL_GetMouseState(&startx, &starty);

	++Projectile::counter;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 9;
	srcRect.h = 9;

	startx += Game::camera.x;
	starty += Game::camera.y;

	destRect.x = xpos;
	destRect.y = ypos;

	texture = TextureManager::LoadTexture("assets/projectile.png", renderer);

}

void Projectile::init()
{

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 9;
	srcRect.h = 9;

	destRect.w = 9;
	destRect.h = 9;

	move.setPositionx(destRect.x);
	move.setPositiony(destRect.y);

}

void Projectile::update()
{
	destRect.x = static_cast<int>(move.getPositionx() - Game::camera.x);
	destRect.y = static_cast<int>(move.getPositiony() - Game::camera.y);

	Vector2D velocity;

	float dx = move.getPositionx() - startx;
	float dy = move.getPositiony() - starty;
	double angle = atan(dy / dx);


	if (startx > move.getPositionx())
	{
		velocity.x = static_cast<float>(cos(angle)) * speed;
		velocity.y = static_cast<float>(sin(angle)) * speed;
	}
	else
	{
		velocity.x = static_cast<float>(cos(angle)) * -speed;
		velocity.y = static_cast<float>(sin(angle)) * -speed;
	}


	move.setPositionx(move.getPositionx() + velocity.x);
	move.setPositiony(move.getPositiony() + velocity.y);

	move.update();

}

void Projectile::draw()
{
	TextureManager::Draw(texture, srcRect, destRect, renderer, SDL_FLIP_NONE);
}

SDL_Rect Projectile::getdestRect()
{
	return destRect;
}

Projectile::~Projectile()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	renderer = nullptr;
	--Projectile::counter;
}

int Projectile::getCounter()
{
	return Projectile::counter;
}

void Projectile::setCounter(int c)
{
	c = Projectile::counter;
}

int Projectile::getStartx()
{
	return startx;
}

int Projectile::getStarty()
{
	return starty;
}
