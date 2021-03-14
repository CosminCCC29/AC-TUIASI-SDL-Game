#include "Zombie.h"
#include "Entity.h"
#include "TextureManager.h"
#include <SDL.h>
#include "Game.h"
#include "Player.h"

extern Player* player;

Zombie::Zombie(const char* textureSheet, SDL_Renderer* renderer, int x, int y) : Entity(textureSheet, renderer, x, y), angle(0)
{

}

Zombie::~Zombie()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	renderer = nullptr;
}

void Zombie::init()
{
	srcRectangle.h = 171;
	srcRectangle.w = 191;
	srcRectangle.x = 0;
	srcRectangle.y = 0;

	destRectangle.w = 91;
	destRectangle.h = 71;

	move.setPositionx(destRectangle.x);
	move.setPositiony(destRectangle.y);
}

void Zombie::update()
{
	followUpdate();
	Entity::update();
}

void Zombie::draw()
{
	SDL_RenderCopyEx(renderer, texture, &srcRectangle, &destRectangle, angle, NULL, SDL_FLIP_NONE);
}

SDL_Rect Zombie::getdestRect()
{
	return this->destRectangle;
}

void Zombie::setAngle(float ang)
{
	angle = ang;
}

void Zombie::followUpdate()
{
	float dx = move.getPositionx() - player->move.getPositionx();
	float dy = move.getPositiony() - player->move.getPositiony();
	float angle = atan(dy / dx);


	float angle_deg = (angle * 180.0000) / 3.1416;

	if (player->move.getPositionx() < move.getPositionx())
	{
		angle_deg += 180;
	}

	setAngle(angle_deg);

	move.setVelocityx(cos(angle));
	move.setVelocityy(sin(angle));

	if (player->move.getPositionx() < move.getPositionx())
	{
		move.setSpeedx(-3);
		move.setSpeedy(-3);
	}
	else
	{
		move.setSpeedx(3);
		move.setSpeedy(3);
	}

}