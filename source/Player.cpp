#include "Player.h"

Player::Player(){

}

void Player::init(SDL_Renderer* r){
	renderer = r;

	surface = IMG_Load("romfs:/assets/actors/players/main.png");
	sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	debug = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 30);
}

void Player::update(){
	hidJoystickRead(&jPosR, CONTROLLER_P1_AUTO, JOYSTICK_RIGHT);
	hidJoystickRead(&jPosL, CONTROLLER_P1_AUTO, JOYSTICK_LEFT);
	
	updateMovement();
	updateAim();
}

void Player::updateMovement(){
	dx = dx/1.2f;
	dy = dy/1.2f;
	if (abs(playerSpeed*(jPosL.dx/32768.0f)) > abs(dx))
		dx = playerSpeed*(jPosL.dx/32768.0f);
	if (abs(playerSpeed*(jPosL.dy/32768.0f)) > abs(dy))
		dy = playerSpeed*(jPosL.dy/32768.0f);

	x+=dx;
	y-=dy;
	

	if (x > 1920)
		x -= 1920;
	if (x < 0)
		x += 1920;
	if (y < 0)
		y += 1080;
	if (y > 1080)
		y -= 1080;
}

void Player::updateAim(){
	if (jPosR.dx != 0 || jPosR.dy != 0)
		angle=atan2(jPosR.dx, jPosR.dy);
}

void Player::draw(){
	renderColorText(renderer, debug, 0,0, "jPosL: (" + to_string(jPosL.dx) + "dx, " + to_string(jPosL.dy) + "dy)\njPosR: (" + to_string(jPosR.dx) + "dx, " + to_string(jPosR.dy) + "dy)\nmoveVector: (" + to_string(dx) + "dx, " + to_string(dy) + "dy)", {0,255,0});
	renderTextureRotated(renderer, sprite.texture, (int)x, (int)y, (angle/M_PI)*180);
}