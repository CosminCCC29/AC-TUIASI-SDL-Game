#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"


Player::Player(const char* path, SDL_Renderer* renderer) : renderer(renderer), lives("assets/Lives.png", renderer), angle(0)
{
	playerFlip = SDL_FLIP_NONE;

	destRect.x = 0;	srcRect.x = 0;
	destRect.y = 0; srcRect.y = 0;
	destRect.w = 0; srcRect.w = 0;
	destRect.h = 0; srcRect.h = 0;

	texture = TextureManager::LoadTexture(path, renderer);
}

void Player::setTex(const char* path)
{
	texture = TextureManager::LoadTexture(path, renderer);
}

void Player::init()
{
	lives.init();

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 258;
	srcRect.h = 152;

	destRect.w = 101;
	destRect.h = 81;

	destRect.x = 900;
	destRect.y = 900;

	move.setPositionx(destRect.x);
	move.setPositiony(destRect.y);

}

void Player::update()
{

	move.setSpeedx(10);
	move.setSpeedy(10);
	destRect.x = static_cast<int>(move.getPositionx() - Game::camera.x);
	destRect.y = static_cast<int>(move.getPositiony() - Game::camera.y);

	move.update();

	angleUpdate();

	lives.update();

}

void Player::draw()
{
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, NULL, playerFlip);
	lives.draw();
}

SDL_Rect Player::getdestRect()
{
	return this->destRect;
}

void Player::setAngle(float ang)
{
	angle = ang;
}

void Player::angleUpdate()
{
	int x = 0, y = 0;

	SDL_GetMouseState(&x, &y);
	x += Game::camera.x;
	y += Game::camera.y;

	float dx = x - (move.getPositionx() + this->destRect.w / 2);
	float dy = y - (move.getPositiony() + this->destRect.h / 2);

	float angle = atan(dy / dx);

	float angle_deg = (angle * 180.0000) / 3.1416;

	if (move.getPositionx() + this->destRect.w / 2 > x)
	{
		angle_deg += 180;
	}

	this->angle = angle_deg;
}

void Player::windowsCollision()
{
	if (move.getPositionx() < 64)
	{
		move.setPositionx(64);
		move.setVelocityx(0);
	}

	if (move.getPositionx() > (Game::camera.x + Game::camera.w - 101 - 64))
	{
		move.setPositionx(Game::camera.x + Game::camera.w - 101 - 64);
		move.setVelocityx(0);
	}

	if (move.getPositiony() < 64)
	{
		move.setPositiony(64);
		move.setVelocityy(0);
	}

	if (move.getPositiony() > Game::camera.y + Game::camera.h - 81 - 64)
	{
		move.setPositiony(Game::camera.y + Game::camera.h - 81 - 64);
		move.setVelocityy(0);
	}

}

void Player::setLives(int set)
{
	lives.setLives(set);
}
int Player::getLives()
{
	return lives.getLives();
}

void Player::UpdateLivesFlag(int i, bool boolVal)
{
	this->lives.UpdateFlag(i, boolVal);
}

bool Player::getLiveFlag(int i)
{
	return lives.getFlag(i);
}
