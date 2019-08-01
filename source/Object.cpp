#include "Object.h"

Object::Object(){

}

void Object::init(SDL_Renderer* r, SDL_Texture* texture , float s, float sx, float sy, float tx, float ty){
	renderer = r;

	sprite.texture = texture;

	float dx = sx-tx;
	float dy = sy-ty;

	direction = atan2(-dy, -dx);
	speed = s;
	angle = (rand() % 3600)/10;
	angle_change = (float)0.5-(rand() % 100)/(float)1000;

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
	renderTextureRotated(renderer, sprite.texture, x, y, angle);
}