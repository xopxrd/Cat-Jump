#include "SDL.h"
#include "SDL_image.h"
#include "Player.hpp"
#include "Block.hpp"

#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;

const float gravity = 0.4f;
const float friction = 0.2f;
const int frameWidth = 32;
int counter = 0;

Player::Player(float x, float y, SDL_Texture* walk)
:playerTex(walk)
{
	playerRect.x = 128;
	playerRect.y = 0;
	playerRect.w = 32;
	playerRect.h = 32;

	this->x = x;
	this->y = y;
}

SDL_Texture* Player::getTex(){
	return playerTex;
}

float Player::getX(){
	return x;
}

float Player::getY(){
	return y;
}

void Player::walkFrame(){
	if (playerRect.x >= 128)
		playerRect.x = 0;
}

void Player::idleFrame(){
	if (playerRect.x >= 192)
		playerRect.x = 128;
}

void Player::setFrameWidth(int frameWidth){
	counter++;
	if (counter >= 12){
		counter = 0;
		playerRect.x += frameWidth;
	}

	else if (counter >= 5 && velocityX != 0){
		counter = 0;
		playerRect.x += frameWidth;	
	}
}

SDL_Rect Player::getPlayerRect(){
	return playerRect;
}

SDL_RendererFlip Player::getFlip(){
	return flip;
}

int Player::head(){
	return y;
}

int Player::foot(){
	return y + 32;
}

void Player::setFlip(const Uint8* keystate){
	if (keystate[SDL_SCANCODE_RIGHT])
		flip = SDL_FLIP_NONE;
	else if (keystate[SDL_SCANCODE_LEFT])
		flip = SDL_FLIP_HORIZONTAL;
}

void Player::setX(float x){
	this->x = x;
}

void Player::setY(float y){
	this->y = y;
}

void Player::spriteAnim(){
	if (velocityY < 0)
		playerRect.x = 192;

	if (velocityY > 0){
		playerRect.x = 64;
	}

	if (grounded && velocityX == 0){
		setFrameWidth(32);
		idleFrame();
	}
}

void Player::intersect(Block& block){
	spriteAnim();

	// kejedot block
	if (getX() + 32 > block.getX() && getX() < block.getX() + block.getWidth())
	{
		if (getY() < block.getY() + block.getHeight() && getY() + 32 > block.getY() && velocityY < 0)
			velocityY *= -1;
	}		

	// nepak block
	if ((getX() + 32 > block.getX()) && (getX() < block.getX() + block.getWidth())
	&& (getY() + 32 > block.getY()) && getY() + 32 < block.getY() + block.getHeight())
	{
		velocityY = 0.0f;
		grounded = true;
		if ((keystate[SDL_SCANCODE_UP] && grounded)){
			velocityY = -15.0f;
			grounded = false;
		}
	}
	else
		grounded = false;
}

void Player::playerUpdate(){
	keystate = SDL_GetKeyboardState(NULL);
	setX(this->x + velocityX);
	setY(this->y + velocityY);

	if (keystate[SDL_SCANCODE_RIGHT]){
		setFlip(keystate);
		setFrameWidth(frameWidth);
		walkFrame();

		velocityX += 0.5f;
	}

	if (keystate[SDL_SCANCODE_LEFT]){
		setFlip(keystate);
		setFrameWidth(frameWidth);
		walkFrame();

		velocityX -= 0.5f;
	}

	if (velocityX >= maxSpeed)
		velocityX = maxSpeed;
	if (velocityX <= maxSpeed * -1)
		velocityX = maxSpeed * -1;

	// kudu 1 scope
	{
		if (this->y >= SCREEN_HEIGHT - 32){
			this->y = SCREEN_HEIGHT - 32;
			grounded = true;
			velocityY = 0.0f;
		}

		if ((keystate[SDL_SCANCODE_UP] && grounded)){
			velocityY = -15.0f;
			grounded = false;
		}
	}

	// gesekan
	if (velocityX > 0){
		velocityX -= friction;
		if (velocityX < 0)
			velocityX = 0;
	}

	if (velocityX < 0){
		velocityX += friction;
		if (velocityX > 0)
			velocityX = 0;
	}

	if (!grounded)
		velocityY += gravity;

	if (this->x <= 0)
		this->x = 0;
	if (this->x >= SCREEN_WIDTH - 32)
		this->x = SCREEN_WIDTH - 32;
}