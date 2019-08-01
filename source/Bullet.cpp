#include "Bullet.h"

Bullet::Bullet(){

}

void Bullet::init(SDL_Renderer* r, SDL_Texture* texture, float d, float s, float sx, float sy){
    renderer = r;
    sprite.texture = texture;

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

void Bullet::draw(){
	renderTextureRotated(renderer, sprite.texture, x, y, direction);
}

bool Bullet::isDead(){
    return !alive;
}