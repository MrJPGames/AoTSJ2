#include "Game.h"

Game::Game(){

}

void Game::init(SDL_Renderer* r){
	player.init(r);

	renderer = r;

	debug = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 30);

	surface = IMG_Load("romfs:/assets/actors/objects/placeholder.png");
	defaultObject.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	surface = IMG_Load("romfs:/assets/actors/bullets/placeholder.png");
	defaultBullet.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Game::draw(){
	drawObjects();
	drawBullets();

	//Player on top
	player.draw();
}

void Game::drawObjects(){
	ObjectNode *ptr = objects;
	while (ptr != NULL){
		ptr->o.draw();
		ptr = ptr->next;
	}
}

void Game::drawBullets(){
	BulletNode *ptr = bullets;
	while(ptr != NULL){
		ptr->b.draw();
		ptr = ptr->next;
	}
}

void Game::update(){
	u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
	u32 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

	player.update();
	updateObjects();
	updateBullets();

	if (kDown & KEY_X)
		addObject();
	if (kDown & KEY_ZR)
		addBullet();
}

void Game::updateObjects(){
	ObjectNode *ptr = objects;
	ObjectNode *prev = NULL;
	while (ptr != NULL){
		ptr->o.update();
		if (ptr->o.isDead()){
			if (prev != NULL)
				prev->next = ptr->next;
			else
				objects = ptr->next;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

void Game::updateBullets(){
	BulletNode *ptr = bullets;
	BulletNode *prev = NULL;
	while (ptr != NULL){
		ptr->b.update();
		if (ptr->b.isDead()){
			if (prev != NULL)
				prev->next = ptr->next;
			else
				bullets = ptr->next;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

void Game::addObject(){
	Object obj;
	obj.init(renderer, defaultObject.texture, 0, 3, player.getX(), player.getY());


	ObjectNode *o = new ObjectNode;
	o->o = obj;
	o->next = objects;

	objects = o;
}

void Game::addBullet(){
	Bullet obj;
	obj.init(renderer, defaultBullet.texture, player.getAim(), 10, player.getX(), player.getY());


	BulletNode *b = new BulletNode;
	b->b = obj;
	b->next = bullets;

	bullets = b;
}