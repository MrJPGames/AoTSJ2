#include "Object.h"

Object::Object(){

}

void Object::init(SDL_Renderer* r, SDL_Texture* texture , float d, float s, float sx, float sy){
	renderer = r;

	sprite.texture = texture;

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

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT){
		alive = false;
	}
}

void Object::draw(){
	renderTextureRotated(renderer, sprite.texture, x, y, angle);
}