#include "Game/Object.h"

Object::Object(){
	scoreValue = 1000;
	spriteDir = "romfs:/assets/actors/objects/";
}

void Object::init(SDL_Renderer* r, TextureManager* tm , float s, float sx, float sy, float tx, float ty){
	renderer = r;

	sprite = tm->getRandomTexture(spriteDir);

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

	//Make every sprite act like it's a 16x16 sprite
	float widthScale = w/16.0f;
	scale = scale/widthScale;

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

int Object::getValue(){
	return scoreValue;
}

void Object::draw(){
	renderTextureScaledRotated(renderer, sprite, x, y, scale, angle);
}