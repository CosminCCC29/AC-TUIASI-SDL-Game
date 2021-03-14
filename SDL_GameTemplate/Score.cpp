#include "Score.h"
#include "TextureManager.h"
#include <iostream>

Score::Score()
{
	this->destScore.x = 0;
	this->destScore.y = 0;
	this->destScore.w = 0;
	this->destScore.h = 0;

	this->destRectScore.x = 0;
	this->destRectScore.y = 0;
	this->destRectScore.w = 0;
	this->destRectScore.h = 0;

	this->text_colorScore = {0,0,0,0};
	scoreFontsize = 0;
	font = nullptr;
	score = 0;

	scoreTex = nullptr;
	scoreTexture = nullptr;
	scoreSurface = nullptr;
	renderer = nullptr;
}

Score::Score(SDL_Renderer* renderer)
{
	this->destScore.x = 0;
	this->destScore.y = 0;
	this->destScore.w = 0;
	this->destScore.h = 0;

	this->destRectScore.x = 0;
	this->destRectScore.y = 0;
	this->destRectScore.w = 0;
	this->destRectScore.h = 0;

	this->text_colorScore = { 0,0,0,0 };
	scoreFontsize = 0;
	font = nullptr;
	score = 0;

	scoreTex = nullptr;
	scoreTexture = nullptr;
	scoreSurface = nullptr;
	this->renderer = renderer;
}

void Score::init()
{
	score = 0;

	scoreFontsize = 72;
	text_colorScore = { 20, 20, 20 };

	try 
	{
		font = TTF_OpenFont("assets/ComicSans.ttf", scoreFontsize);

		if (font == nullptr)
		{
			throw "Eroare la alocarea fontului.";
		}
	}

	catch (const char *ex)
	{
		std::cout << ex;
	}

	destRectScore.h = 64;
	destRectScore.w = 100;

	destRectScore.x = 1330;
	destRectScore.y = 0;

	destScore.h = 64;
	destScore.w = 250;

	destScore.x = 1090;
	destScore.y = 0;

}

void Score::update()
{
	scoreSurface = TTF_RenderText_Solid(font, convertScore(), text_colorScore);
	scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

	scoreSurface = TTF_RenderText_Solid(font, "Score: ", text_colorScore);
	scoreTex = SDL_CreateTextureFromSurface(renderer, scoreSurface);
}

void Score::draw()
{
	if (scoreTexture && scoreTex)
	{
		SDL_RenderCopy(renderer, scoreTexture, NULL, &destRectScore);
		SDL_RenderCopy(renderer, scoreTex, NULL, &destScore);
	}
}

void Score::setSurface(SDL_Window* window) 
{
	scoreSurface = SDL_GetWindowSurface(window);
}

Score::~Score()
{
	SDL_DestroyTexture(scoreTexture);
	SDL_FreeSurface(scoreSurface);
	scoreTexture = nullptr;
	scoreSurface = nullptr;

	renderer = nullptr;

}

char *Score::convertScore()
{
	char x[100];
	sprintf(x, "%d", score);

	return x;
}