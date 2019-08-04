#include "Game/Object.h"

Object::Object(){

}

void Object::init(SDL_Renderer* r, TextureManager* tm , float s, float sx, float sy, float tx, float ty){
	renderer = r;

	sprite = tm->getTexture("romfs:/assets/actors/objects/placeholder.png");

	float dx = sx-tx;
	float dy = sy-ty;

	direction = atan2(-dy, -dx);
	speed = s;
	angle = (rand() % 3600)/10.0f;
	angle_change = (100-(rand() % 200))/100.0f;

	x = sx;
	y = sy;
}

bool Object::isDead(){
	return !alive;
}

void Object::update(){
	x+=cos(direction)*speed;
	y+=sin(direction)*speed;
	angle+=angle_change;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT){
		alive = false;
	}
}

float Object::getX(){
	return x;
}

float Object::getY(){
	return y;
}

float Object::getSize(){
	return 75;
}

void Object::kill(){
	alive = false;
}

void Object::draw(){
	renderTextureRotated(renderer, sprite, x, y, angle);
}