#pragma once
#include "Component.h"
#include "Movement.h"

class Projectile : public Component
{
public:
	Projectile(int speed, int xpos, int ypos, SDL_Renderer* renderer);

	void init();
	void draw();
	void drawUpdate() {};
	SDL_Rect getdestRect();

	static int getCounter();
	void setCounter(int c);
	int getStartx();
	int getStarty();
	
	void update();

	~Projectile();

	Movement move;
private:

	int startx;
	int starty;
	static int counter;

	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect, destRect;

	int speed;

};