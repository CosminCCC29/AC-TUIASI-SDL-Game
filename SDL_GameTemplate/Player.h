#pragma once
#include "Component.h"
#include "Movement.h"
#include "Lives.h"
#include "Collision.h"
#include "Projectile.h"

class Player : public Component
{
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_RendererFlip playerFlip;
	Lives lives;
	float angle;


public:

	Movement move;
	Player() = default;
	Player(const char* path, SDL_Renderer* renderer);

	void setTex(const char* path);

	void init() override;
	void update() override;
	void draw() override;
	void drawUpdate() {};
	SDL_Rect getdestRect() override;
	
	void setLives(int set);
	int getLives();

	void UpdateLivesFlag(int i, bool flag);
	bool getLiveFlag(int i);

	void setAngle(float ang);
	void angleUpdate();

	void windowsCollision();

};
