#include <iostream>
#include <time.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Render.hpp"
#include "Player.hpp"
#include "Block.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

int main(int argc, char *argv[])
{
	srand(time(0));

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (SDL_Init(SDL_INIT_VIDEO) > 0 && SDL_Init(SDL_INIT_AUDIO) > 0) 
		std::cout << "SDL init failed: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG init failed: " << SDL_GetError() << std::endl;

	Render* window = new Render("new", SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Texture* playerTex = window->loadTexture("../../new/res/textures/cat.png");
	SDL_Texture* blockTex = window->loadTexture("../../new/res/textures/block.png");

	Player* cat = new Player(0, SCREEN_HEIGHT - 32, playerTex);
	// Block* block = new Block(blockTex);
	Block* emptyBlock[20];

	for (int i = 0; i < 10; i++){
		emptyBlock[i] = new Block(blockTex);
		emptyBlock[i]->setPos(rand() % 700, rand() % 600);
	}

	bool gameRunning = true;
	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		cat->playerUpdate();

		for (int i = 0; i < 10; i++)
			cat->intersect(*emptyBlock[i]);

		window->clear();
		window->render(*cat);

		for (int i = 0; i < 10; i++)
			window->render(*emptyBlock[i]);

		window->display();
	}

	window->cleanUp();
	for (int i = 0; i < 10; i++)
		delete emptyBlock[i];
	
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}