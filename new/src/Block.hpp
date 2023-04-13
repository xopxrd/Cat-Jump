#pragma once

class Block {
private:
	float x, y;
	SDL_Texture* blockTex;
	SDL_Rect blockRect;

public:
	Block(SDL_Texture*);
	float getX();
	float getY();
	int getWidth();
	int getHeight();
	SDL_Rect getBlockRect();
	SDL_Texture* getTex();
	void setPos(float, float);
};