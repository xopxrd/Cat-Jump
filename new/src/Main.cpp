#include <iostream>
#include <ctime>
#include <cmath>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Render.hpp"
#include "Player.hpp"
#include "Block.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 640;

const int NOT_PLAY = 0;
const int PLAY = 1;
const int DEATH = 2;

SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };

bool gameRunning = true;
bool mainMenu = true;
bool playedDeathSFX = false;

int main(int argc, char *argv[])
{	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	Render* window = new Render("Cat Jump", SCREEN_WIDTH, SCREEN_HEIGHT);

	TTF_Font* font32 = TTF_OpenFont("../../Cat Jump/res/fonts/cocogoose.ttf", 32);
	TTF_Font* font32_outline = TTF_OpenFont("../../Cat Jump/res/fonts/cocogoose.ttf", 32);
	TTF_Font* font24 = TTF_OpenFont("../../Cat Jump/res/fonts/cocogoose.ttf", 24);
	TTF_Font* font16 = TTF_OpenFont("../../Cat Jump/res/fonts/cocogoose.ttf", 16);
	TTF_SetFontOutline(font32_outline, 3); 

	SDL_Texture* playerTex = window->loadTexture("../../Cat Jump/res/textures/cat.png");
	SDL_Texture* blockTex = window->loadTexture("../../Cat Jump/res/textures/block.png");
	SDL_Texture* logo = window->loadTexture("../../Cat Jump/res/textures/logo.png");
	SDL_Texture* deathOverlay = window->loadTexture("../../Cat Jump/res/textures/death_overlay.png");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "error: " << Mix_GetError() << std::endl;

	Mix_Music* backgroundMusic = Mix_LoadMUS("../../Cat Jump/res/sound/Wallpaper.mp3");
	Mix_Chunk* fallSound = Mix_LoadWAV("../../Cat Jump/res/sound/mixkit-falling-hit-on-gravel-756.wav");

	Player* cat = new Player(0, SCREEN_HEIGHT - 32, playerTex);
	Block* emptyBlock[10];
	int counter = 0;

	for (int i = 0; i < 10; i++)
	{
		counter += 64;
		emptyBlock[i] = new Block(blockTex);
		emptyBlock[i]->setPos(rand() % (SCREEN_WIDTH - 32) + 1, counter);
	}

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					gameRunning = false;
					break;
				}

				case SDL_MOUSEBUTTONDOWN:
		    	{
		    		if (mainMenu)
		    		{
		    			if (event.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 2500)
		    			{
		    				mainMenu = false;
		    				if( Mix_PlayingMusic() == 0 )
		                    {
		                        // Play the music
		                        if( Mix_PlayMusic( backgroundMusic, -1 ) == -1 )
		                            return 1;
		                    }
		    			}
		    		}
		    		break;
		    	}
			}
		}

		if (mainMenu)
		{
			if (SDL_GetTicks() < 2500)
			{
				window->clear();
				window->renderCenter(0, sin(SDL_GetTicks()/100) * 2 - 4, "xopxrd", font24, white);
				window->display(); // update screen
			}
			else
			{
				window->clear();
				window->render(0, 0, logo);
				window->renderCenter(0, 90 + sin(SDL_GetTicks()/100) * 2 - 4, "Click to start", font24, white);
				window->display();
			}
		}
		else
		{
			cat->playerUpdate();
			for(int i = 0; i < 10; i++)
				cat->intersect(*emptyBlock[i]);
			

			window->clear();
			window->render(*cat);

			for(int i = 0; i < 10; i++)
				window->render(*emptyBlock[i]);

			window->render(0, 0, cat->getScore(), font32_outline, black);
			window->render(3, 3, cat->getScore(), font32, white);
			window->render(3, 44, cat->getHighscore(), font16, white);

			if (cat->getCondition() == PLAY)
				playedDeathSFX = false;
			
			if (cat->getCondition() == DEATH)
			{
				Mix_HaltMusic();
				window->render(0, 0, deathOverlay);
				window->renderCenter(0, -24, "You die...", font24, white);
				window->renderCenter(0, 12, "Press space to retry", font16, white);
				if (!playedDeathSFX)
				{
					Mix_PlayChannel(1, fallSound, 0);
				}
				playedDeathSFX = true;

				if (cat->getKeystate()[SDL_SCANCODE_SPACE])
				{	
					Mix_PlayMusic(backgroundMusic, -1);
					cat->reset();
				}
			}

			window->display();
		}
	}
	
	window->cleanUp();
	
	for(int i = 0; i < 10; i++)
		delete emptyBlock[i];
	
	TTF_CloseFont(font32);
	TTF_CloseFont(font32_outline);
	TTF_CloseFont(font24);
	TTF_CloseFont(font16);
	Mix_FreeChunk(fallSound);
	Mix_FreeMusic(backgroundMusic);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}