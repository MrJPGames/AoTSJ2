#include "Game/Particle.h"

Particle::Particle(){}

void Particle::init(SDL_Renderer* r, TextureManager* tm, string path, float sx, float sy, int dur, float dir, float s, float sa, float ea, float ss, float es, float as){
    renderer   = r;
    sprite     = tm->getTexture(path);
    duration   = dur;
    direction  = dir;
    speed      = s;
    startAlpha = sa;
    endAlpha   = ea;
    startScale = ss;
    endScale   = es;
    angleSpeed = as;
    x          = sx;
    y          = sy;
}

void Particle::initDir(SDL_Renderer* r, TextureManager* tm, string path, float sx, float sy, int dur, float dir, float s, float sa, float ea, float ss, float es, float as){
    renderer   = r;
    sprite     = tm->getRandomTexture(path);
    duration   = dur;
    direction  = dir;
    speed      = s;
    startAlpha = sa;
    endAlpha   = ea;
    startScale = ss;
    endScale   = es;
    angleSpeed = as;
    x          = sx;
    y          = sy;
}

void Particle::init(SDL_Renderer* r, TextureManager* tm, string path, float sx, float sy, int dur, float sa, float ea, float ss, float es, float as){
    init(r, tm, path, sx, sy, dur, 0, 0, sa, ea, ss, es, as);
}

void Particle::init(SDL_Renderer* r, image i, SDL_Rect tRect, float sx, float sy, int dur, float dir, float s, float sa, float ea, float ss, float es, float a, float as){
    renderer   = r;
    sprite     = i;
    duration   = dur;
    direction  = dir;
    speed      = s;
    startAlpha = sa;
    endAlpha   = ea;
    startScale = ss;
    endScale   = es;
    angleSpeed = as;
    x          = sx;
    y          = sy;
    angle      = a;
    texRect    = tRect;
    useTexRect = true;
}

void Particle::update(){
	x += cos(direction)*speed;
	y += sin(direction)*speed;
	angle += angleSpeed;
    scale = startScale + (timer/(float)duration) * (endScale-startScale);
    alpha = startAlpha + (timer/(float)duration) * (endAlpha-startAlpha);
    timer++;
}

void Particle::draw(){
    if (useTexRect){
        renderTextureScaledRotatedAlpha(renderer, sprite, x, y, scale, angle, alpha, &texRect);
    }else{
        renderTextureScaledRotatedAlpha(renderer, sprite, x, y, scale, angle, alpha, NULL);
    }
}

bool Particle::isDead(){
    return timer > duration;
}