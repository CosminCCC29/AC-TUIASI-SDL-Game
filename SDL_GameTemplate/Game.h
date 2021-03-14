#pragma once
#include <SDL.h>
#include "Score.h"
#include <exception>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	void cameraUpdate() const;
	void gameCollisionsUpdate();

	void setEnemyMaxNumber(unsigned int x);
	unsigned int static getEnemyMaxNumber();

	static SDL_Event event;
	static SDL_Rect camera;

private:

	static unsigned int enemyMaxNumber;
	bool isRunning;
	SDL_Renderer* renderer;
	SDL_Window* window;

	Score* score;
	SDL_Rect destImage;
	SDL_Texture* ImageScreenTexture;
	SDL_Surface* ImageScreenSurface;
};
