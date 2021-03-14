#pragma once
#include "Component.h"
#include "SDL_ttf.h"
#include <exception>

class Score : public Component
{
	SDL_Texture* scoreTexture;
	SDL_Texture* scoreTex;
	SDL_Surface* scoreSurface;
	SDL_Renderer* renderer;

	SDL_Rect destRectScore;
	SDL_Rect destScore;
	SDL_Color text_colorScore;
	TTF_Font* font;

	int score;
	int scoreFontsize;

public:

	Score();
	Score(SDL_Renderer* renderer);
	~Score();

	void init();
	void draw();
	void drawUpdate() {}
	void update();
	SDL_Rect getdestRect() { return destRectScore; };

	void setSurface(SDL_Window* window);
	void setScore(int score) { this->score = score; }
	int getScore() { return score; }
	char *convertScore();
};