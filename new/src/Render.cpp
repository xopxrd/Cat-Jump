#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Render.hpp"
#include "Player.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 640;

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

void Render::render(float p_x, float p_y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h); 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void Render::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
}

void Render::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h; 

	SDL_Rect dst;
	dst.x = SCREEN_WIDTH/2 - src.w/2 + p_x;
	dst.y = SCREEN_HEIGHT/2 - src.h/2 + p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
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