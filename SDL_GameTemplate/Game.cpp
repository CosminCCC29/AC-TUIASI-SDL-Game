#include <iostream>
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "GameObject.h"
#include "Lives.h"
#include "Collision.h"
#include "Entity.h"
#include "Zombie.h"

#include <cstdlib> 
#include <ctime>
#include <math.h> 


Map* map;
Player* player;
Projectile* proj[100];

SDL_Rect Game::camera = { 0,0, 1440, 736 };

Component* Object[100];
Component* zombie[100];

SDL_Event Game::event;
unsigned int Game::enemyMaxNumber;
static int shot = 0;

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), ImageScreenSurface(nullptr), ImageScreenTexture(nullptr), score(nullptr)
{
	this->destImage.x = 0;
	this->destImage.y = 0;
	this->destImage.w = 0;
	this->destImage.h = 0;
}

Game::~Game()
{
	delete player;

	for (int i = 0; i < 100; ++i)
	{
		if (Object[i])
		{
			delete Object[i];
		}

		if (zombie[i])
		{
			delete zombie[i];
		}
	}
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;
		auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != nullptr)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer != nullptr)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	TTF_Init();

	
		SDL_Surface* mainMenu = SDL_GetWindowSurface(window);
		mainMenu = IMG_Load("assets/newgame.png");
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, mainMenu);

		ImageScreenSurface = SDL_GetWindowSurface(window);
		ImageScreenSurface = IMG_Load("assets/DeathScreen.png");
		ImageScreenTexture = SDL_CreateTextureFromSurface(renderer, ImageScreenSurface);

		destImage.w = 848;
		destImage.h = 480;
		destImage.x = 296;
		destImage.y = 100;

	bool startGame = 1;
	bool menuBar = 1;
	while (startGame)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_w:
				menuBar = 1;
				texture = TextureManager::LoadTexture("assets/newgame.png", renderer);

				break;


			case SDLK_s:
				menuBar = 0;
				texture = TextureManager::LoadTexture("assets/quitgame.png", renderer);

				break;

			case SDLK_SPACE:

				if (menuBar)
				{
					startGame = 0;
				}
				else
				{
					startGame = 0;
					isRunning = false;
				}

				break;

			case SDLK_ESCAPE:
				startGame = 0;
				isRunning = 0;
				break;
			}
		}
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	map = new Map(renderer);

	this->score = new Score(renderer);
	this->score->init();
	this->score->setSurface(window);

	player = new Player("assets/player2.png", renderer);

	try
	{
		if (!player)
			throw "Eroare la initializarea player-ului.";
	}

	catch (const char*& ex)
	{
		std::cout << ex << std::endl;
	}

	player->init();

	srand(time(0));

	setEnemyMaxNumber(8);
	for (unsigned int i = 0; i < getEnemyMaxNumber(); ++i)
	{
		zombie[i] = new Zombie("assets/enemy.png", renderer, (rand() % ((1440 * 2 - 64 * 2) - 64) + 1) + 64, (rand() % ((736 * 2 - 64 * 2) - 64) + 1) + 64);

		try
		{
			if (!zombie[i])
				throw "Eroare la alocarea initializarea inamicilor.";
		}

		catch (const char*& ex)
		{
			std::cout << ex << std::endl;
		}

		zombie[i]->init();
	}

}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_w:
				player->move.setVelocityy(-1);
				break;

			case SDLK_s:
				player->move.setVelocityy(1);
				break;

			case SDLK_a:
				player->move.setVelocityx(-1);
				break;

			case SDLK_d:
				player->move.setVelocityx(1);
				break;

			case SDLK_1:
				setEnemyMaxNumber(8);
				score->init();
				player->init();

				for (unsigned int i = 0; i < getEnemyMaxNumber(); ++i)
				{
					delete zombie[i];
					zombie[i] = nullptr;
				}

				for (int i = 0; i < 100; ++i)
				{
					delete proj[i];
					proj[i] = nullptr;
				}

				break;

			case SDLK_2:
				setEnemyMaxNumber(12);
				score->setScore(1000);
				player->init();

				for (unsigned int i = 0; i < getEnemyMaxNumber(); ++i)
				{
					delete zombie[i];
					zombie[i] = nullptr;
				}

				for (int i = 0; i < 100; ++i)
				{
					delete proj[i];
					proj[i] = nullptr;
				}

				break;

			case SDLK_3:
				setEnemyMaxNumber(20);
				score->setScore(3000);
				player->init();

				for (unsigned int i = 0; i < getEnemyMaxNumber(); ++i)
				{
					delete zombie[i];
					zombie[i] = nullptr;
				}

				for (int i = 0; i < 100; ++i)
				{
					delete proj[i];
					proj[i] = nullptr;
				}

				break;


			case SDLK_ESCAPE:
				isRunning = 0;
				break;

			}
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{

			case SDLK_w:
				player->move.setVelocityy(0);
				break;

			case SDLK_s:
				player->move.setVelocityy(0);
				break;

			case SDLK_a:
				player->move.setVelocityx(0);
				break;

			case SDLK_d:
				player->move.setVelocityx(0);
				break;

			}
		}
	

		if (SDL_WaitEvent)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:

					++shot;

						if (shot == 1)
						{
							int count = Projectile::getCounter() + 1;
							proj[count] = new Projectile(15, static_cast<int>(player->move.getPositionx()) + 101 / 2, static_cast<int>(player->move.getPositiony()) + 81 / 2, renderer);
							proj[count]->init();
						}

				}
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				switch (event.button.button)
				{

				case SDL_BUTTON_LEFT:
					shot = 0;
					break;

				}
			}
		}
}

void Game::update()
{
	cameraUpdate();
	gameCollisionsUpdate();

	player->update();

	

		for (unsigned int i = 0; i < getEnemyMaxNumber(); ++i)
		{
			if (!zombie[i])
			{
				zombie[i] = new Zombie("assets/enemy.png", renderer, (rand() % ((1440 * 2 - 64 * 2) - 64) + 1) + 64, (rand() % ((736 * 2 - 64 * 2) - 64) + 1) + 64);
				zombie[i]->init();

				try
				{
					if (!zombie[i])
						throw "Eroare la alocarea inamicilor.";
				}

				catch (const char*& ex)
				{
					std::cout << ex << std::endl;
				}

			}

			if (zombie[i])
				zombie[i]->update();
		}

		for (int i = 0; i < 100; ++i)
		{
			if (proj[i])
			{
				proj[i]->update();
			}

		}


	score->update();



	switch (score->getScore())
	{
	case 1000:
		setEnemyMaxNumber(12);
		break;

	case 3000:
		setEnemyMaxNumber(20);
		break;

	case 5000:

		//Win screen
		ImageScreenSurface = SDL_GetWindowSurface(window);
		ImageScreenSurface = IMG_Load("assets/win.png");
		ImageScreenTexture = SDL_CreateTextureFromSurface(renderer, ImageScreenSurface);
		destImage.w = 634;
		destImage.h = 320;
		destImage.x = 403;

		bool finishGame = true;
		while (finishGame)
		{
			SDL_PollEvent(&event);

			if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_ESCAPE || event.type == SDL_QUIT)
			{
				isRunning = 0;
				finishGame = false;
			}

			SDL_RenderCopy(renderer, ImageScreenTexture, NULL, &destImage);
			SDL_RenderPresent(renderer);
		}

		break;

	}
}

void Game::cameraUpdate() const
{
	camera.x = static_cast<int>(player->move.getPositionx()) - 1280 / 2;
	camera.y = static_cast<int>(player->move.getPositiony()) - 736 / 2;

	if (camera.x < 0) { camera.x = 0; }
	if (camera.y < 0) { camera.y = 0; }

	if (camera.x > camera.w) { camera.x = camera.w; }
	if (camera.y > camera.h) { camera.y = camera.h; }
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->update();

	for (unsigned int i = 0; i < getEnemyMaxNumber(); ++i)
	{
		if (zombie[i])
			zombie[i]->draw();

	}

	for (int i = 0; i < 100; ++i)
	{
		if (proj[i])
		{
			proj[i]->draw();
		}
	}

	player->draw();

	score->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete score;
	SDL_FreeSurface(ImageScreenSurface);
	SDL_DestroyTexture(ImageScreenTexture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_QUIT;
	std::cout << "Game cleaned" << std::endl;
}

void Game::gameCollisionsUpdate()
{
	player->windowsCollision();

//Projectile - Zombie collision

	for (int j = 0; j < 100; ++j)
	{
		for (unsigned int i = 0; i < Game::getEnemyMaxNumber(); ++i)
		{
			if (zombie[i] && proj[j])
			{

				if (Collision::AABB(proj[j]->getdestRect(), zombie[i]->getdestRect()) == true)
				{
					delete zombie[i];
					zombie[i] = nullptr;

					delete proj[j];
					proj[j] = nullptr;

					score->setScore(score->getScore() + 25);
				}
			}
		}

		if  (proj[j] &&
			(proj[j]->move.getPositionx() - proj[j]->getStartx()) *
			(proj[j]->move.getPositionx() - proj[j]->getStartx()) +

			(proj[j]->move.getPositionx() - proj[j]->getStartx()) *
			(proj[j]->move.getPositionx() - proj[j]->getStartx()) < 10 * 10)

		{
			delete proj[j];
			proj[j] = nullptr;
			return;
		}
		

	}

	//Player - Entity Collision

	for (unsigned int i = 0; i < Game::getEnemyMaxNumber(); ++i)
	{
		if (zombie[i])
		{

			if (Collision::AABB(player->getdestRect(), zombie[i]->getdestRect()) == true)
			{
				if (player->getLiveFlag(i) == true)
				{
					player->setLives(player->getLives() - 1);
					player->UpdateLivesFlag(i, false);
					delete zombie[i];
					zombie[i] = nullptr;
				}
			}
			else
			{
				player->UpdateLivesFlag(i, true);
			}
		}
	}

	//When no lives left

	while (player->getLives() == 0)
	{
		SDL_PollEvent(&Game::event);

		if (Game::event.key.keysym.sym == SDLK_SPACE)
		{
			player->setLives(3);
			score->init();

			player->setTex("assets/player2.png");
			player->init();
			player->move.setVelocityx(0);
			player->move.setVelocityy(0);

			for (unsigned int i = 0; i < Game::getEnemyMaxNumber(); ++i)
			{
				delete zombie[i];
				zombie[i] = nullptr;
				zombie[i] = new Zombie("assets/enemy.png", renderer, rand() % (1440 * 2) + 1 + 64, rand() % (736 * 2) + 1 + 64);
				zombie[i]->init();
			}


			for (int i = 0; i < 100; ++i)
			{
				delete proj[i];
				proj[i] = nullptr;
			}

		}
		
		if (player->getLives() == 0)
		{
			SDL_RenderCopy(renderer, ImageScreenTexture, NULL, &destImage);
			SDL_RenderPresent(renderer);
		}
	}
	



}

void Game::setEnemyMaxNumber(unsigned int x)
{
	Game::enemyMaxNumber = x;
}

unsigned int Game::getEnemyMaxNumber()
{
	return Game::enemyMaxNumber;
}
