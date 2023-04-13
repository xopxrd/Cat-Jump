#include "SDL.h"
#include "SDL_image.h"
#include "Player.hpp"
#include "Block.hpp"

#include <iostream>

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 640;

const float gravity = 0.4f;
const float friction = 0.2f;
const int frameWidth = 32;
int FPS = 0;

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

bool Player::isStart(){
	return start;
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
	FPS++;
	if (FPS >= 12){
		FPS = 0;
		playerRect.x += frameWidth;
	}

	else if (FPS >= 5 && velocityX != 0){
		FPS = 0;
		playerRect.x += frameWidth;	
	}
}

SDL_Rect Player::getPlayerRect(){
	return playerRect;
}

SDL_RendererFlip Player::getFlip(){
	return flip;
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
		setFrameWidth(frameWidth);
		idleFrame();
	}
}

void Player::intersect(Block& block){
	spriteAnim();

	if (getX() + 32 > block.getX() && getX() < block.getX() + block.getWidth())
	{
		// // kejedot block
		// if (getY() < block.getY() + block.getHeight() && getY() + 32 > block.getY() && velocityY < 0)
		// 	velocityY *= -1;

		// nepak block
		if (getY() + 32 > block.getY() && getY() < block.getY() && velocityY > 0)
		{
			grounded = true;
			velocityY = -10.0f;
			score++;
		}
	}	

	else
		grounded = false;

	// gerakan block
	if (start)
	{
		block.setPos(block.getX(), block.getY() + 3);
		if (block.getY() > SCREEN_HEIGHT)
			block.setPos(rand() % (SCREEN_WIDTH - 32) + 1, 0);
	}
}

void Player::playerUpdate()
{
	if (score > highscore)
		highscore = score;

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
		if (!start){
			grounded = true;
			velocityY = 0.0f;
		}

		if ((keystate[SDL_SCANCODE_UP] && grounded && !start)){
			start = true;
			velocityY = -10.0f;
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

	if (start && getY() > SCREEN_HEIGHT)
		reset();
}

void Player::reset(){
	velocityY = 0.0f;
	setX(0);
	setY(SCREEN_HEIGHT - 32);
	start = false;
	score = 0;
}

const char* Player::getScore()
{
	std::string s = std::to_string(score);
	s = "DISTANCE: " + s;
	return s.c_str();
}

const char* Player::getHighscore()
{
	std::string s = std::to_string(highscore);
	s = "BEST: " + s;
	return s.c_str();
}