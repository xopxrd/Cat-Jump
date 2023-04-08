#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#include "Render.hpp"
#include "Player.hpp"

Render::Render(const char* title, int w, int h)
:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "error creating a window: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);	
}

SDL_Texture* Render::loadTexture(const char* filepath){
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(filepath);
	if (surface == NULL)
		std::cout << "error: " << SDL_GetError() << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL)
			std::cout << "error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(surface);

	return texture;
}

void Render::render(Player& player){
	SDL_Rect src;
	src.x = player.getPlayerRect().x;
	src.y = player.getPlayerRect().y;
	src.w = player.getPlayerRect().w;
	src.h = player.getPlayerRect().h;

	SDL_Rect dst;
	dst.x = player.getX();
	dst.y = player.getY();
	dst.w = player.getPlayerRect().w;
	dst.h = player.getPlayerRect().h;

	SDL_RenderCopyEx(renderer, player.getTex(), &src, &dst, 0, NULL, player.getFlip());
}

void Render::render(Block& block){
	SDL_Rect src;
	src.x = block.getBlockRect().x;
	src.y = block.getBlockRect().y;
	SDL_QueryTexture(block.getTex(), NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = block.getX();
	dst.y = block.getY();
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, block.getTex(), &src, &dst);
}

void Render::cleanUp(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;
}

void Render::display(){
	SDL_RenderPresent(renderer);
}

void Render::clear(){
	SDL_RenderClear(renderer);
}