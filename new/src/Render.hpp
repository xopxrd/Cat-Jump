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
	void cleanUp();
	void display();
	void clear();
};