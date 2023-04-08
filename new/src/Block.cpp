#include "SDL.h"
#include "SDL_image.h"

#include "Block.hpp"

Block::Block(SDL_Texture* texture)
{
	blockTex = texture;

	blockRect.x = 0;
	blockRect.y = 0;
	SDL_QueryTexture(blockTex, NULL, NULL, &blockRect.w, &blockRect.h);
}

SDL_Texture* Block::getTex(){
	return blockTex;
}

int Block::getWidth(){
	return blockRect.w;
}

int Block::getHeight(){
	return blockRect.h;
}

SDL_Rect Block::getBlockRect(){
	return blockRect;
}

float Block::getX(){
	return x;
}

float Block::getY(){
	return y;
}

void Block::setPos(float x, float y){
	this->x = x;
	this->y = y;
}