#include "Game/Object.h"
#include <SDL2/SDL2_gfxPrimitives.h>

Object::Object(){}

void Object::init(SDL_Renderer* r, TextureManager* tm , float s, float sx, float sy, float tx, float ty){
	renderer = r;

	sprite = tm->getRandomTexture("romfs:/assets/actors/objects/");

	float dx = sx-tx;
	float dy = sy-ty;

	direction = atan2(-dy, -dx);
	speed = s;
	angle = (rand() % 3600)/10.0f;
	angle_change = (100-(rand() % 200))/100.0f;
	scale = (750+(rand() % 500))/100.0f;
	//Box shaped/circular objects are assumed!!
	int w;
    SDL_QueryTexture(sprite.texture, NULL, NULL, &w, NULL);
	radius = w >> 1;

	//"Fix" scale (higher resolution sprites don't become too masive)
	while (scale*w > 200){
		scale-=5;
	}

	x = sx;
	y = sy;
}

image Object::getTexture(){
	return sprite;
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
	return radius*scale;
}

float Object::getScale(){
	return scale;
}

float Object::getAngle(){
	return angle;
}

float Object::getRadAngle(){
	return angle * PI/180;
}

void Object::kill(){
	alive = false;
}

void Object::draw(){
	Uint32 circleColour = 0xFF0000FF;
	filledCircleColor(renderer, x, y, scale*radius, circleColour);
	renderTextureScaledRotated(renderer, sprite, x, y, scale, angle);
}