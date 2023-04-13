#pragma once
#include "Block.hpp"

class Player {
private:
	float x, y;
	int score = 0;
	int highscore = 0;
	SDL_Texture* playerTex;
	SDL_Rect playerRect;
	SDL_RendererFlip flip;
	float velocityX = 0;
	float velocityY = 0;
	float maxSpeed = 5;
	bool grounded;
	bool start = false;
	const Uint8* keystate;

public:
	Player(float, float, SDL_Texture*);
	float getX();
	float getY();
	SDL_RendererFlip getFlip();
	SDL_Rect getPlayerRect();
	SDL_Texture* getTex();
	bool isStart();
	const char* getScore();
	const char* getHighscore();
	const Uint8* getKeystate();
	void intersect(Block&);
	void setX(float);
	void setY(float);
	void setFrameWidth(int);
	void spriteAnim();
	void walkFrame();
	void idleFrame();
	void setFlip(const Uint8*);
	void playerUpdate();
	void reset();
};