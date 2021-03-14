#pragma once
#include "Component.h"
#include "TextureManager.h"

class Lives : public Component
{
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect, destRect;
	bool flag[50];
	unsigned int lives;

public:

	Lives();
	Lives(const char* path, SDL_Renderer* renderer);

	void init();
	void draw();
	void drawUpdate();
	void update();
	SDL_Rect getdestRect() override;

	void setLives(unsigned int set) { lives = set; };
	int getLives() { return lives; }
	void UpdateFlag(int i, bool flag) { this->flag[i] = flag; }
	bool getFlag(int i) { return this->flag[i]; }

};