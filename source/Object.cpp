#include "Object.h"

Object::Object(){

}

void Object::init(SDL_Renderer* r, float d, float s){
	renderer = r;

	surface = IMG_Load("romfs:/assets/actors/objects/placeholder.png");
	sprite.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	direction = d;
	speed = s;
}

void Object::update(){
	x+=cos(direction)*speed;
	y-=sin(direction)*speed;
	angle+=0.1;
}

void Object::draw(){
	renderTextureRotated(renderer, sprite.texture, x, y, angle);
}