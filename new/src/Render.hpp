#pragma once
#include "Player.hpp"
#include "Block.hpp"

class Render {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	Render(const char*, int, int);
	SDL_Texture* loadTexture(const char*);
	void render(Player&);
	void render(Block&);
	void render(float, float, SDL_Texture*);
	void render(float, float, const char*, TTF_Font*, SDL_Color);
	void renderCenter(float, float, const char*, TTF_Font*, SDL_Color);
	void cleanUp();
	void display();
	void clear();
};