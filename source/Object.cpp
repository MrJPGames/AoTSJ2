#include "Object.h"

Object::Object(){

}

void Object::init(SDL_Renderer* r, float d, float s, float sx, float sy){
	renderer = r;

	surface = IMG_Load("romfs:/assets/actors/objects/placeholder.png");
	sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	direction = d;
	speed = s;

	x = sx;
	y = sy;
}

bool Object::isDead(){
	return !alive;
}

void Object::update(){
	x+=cos(direction)*speed;
	y-=sin(direction)*speed;
	angle+=0.1;

	if (x < 0 || y < 0 || x > 1920 || y > 1080){
		alive = false;
	}
}

void Object::draw(){
	renderTextureRotated(renderer, sprite.texture, x, y, angle);
}