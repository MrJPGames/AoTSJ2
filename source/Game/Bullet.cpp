#include "Game/Bullet.h"

Bullet::Bullet(){

}

void Bullet::init(SDL_Renderer* r, TextureManager *tm, float d, float s, float sx, float sy){
    renderer = r;
    sprite = tm->getRandomTexture("romfs:/assets/actors/bullets/");

    speed = s;
    direction = d;
    x = sx;
    y = sy;
}

void Bullet::update(){
	x+=cos(direction)*speed;
	y+=sin(direction)*speed;

    if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT){
		alive = false;
	}
}

bool Bullet::isDead(){
    return !alive;
}

float Bullet::getX(){
	return x;
}

float Bullet::getY(){
	return y;
}

float Bullet::getSize(){
	return 32;
}

void Bullet::kill(){
    alive = false;
}

void Bullet::draw(){
	renderTextureRotated(renderer, sprite, x, y, (direction/M_PI)*180);
}