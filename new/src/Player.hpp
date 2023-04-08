#pragma once
#include "Block.hpp"

class Player {
private:
	float x, y;
	SDL_Texture* playerTex;
	SDL_Rect playerRect;
	SDL_RendererFlip flip;
	float velocityX = 0;
	float velocityY = 0;
	float maxSpeed = 5;
	bool grounded;
	const Uint8* keystate;

public:
	Player(float, float, SDL_Texture*);
	float getX();
	float getY();
	int head();
	int foot();
	void intersect(Block&);
	void setX(float);
	void setY(float);
	void setFrameWidth(int);
	void spriteAnim();
	void walkFrame();
	void idleFrame();
	void setFlip(const Uint8*);
	SDL_RendererFlip getFlip();
	SDL_Rect getPlayerRect();
	void playerUpdate();
	SDL_Texture* getTex();
};