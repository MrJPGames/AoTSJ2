#include "Game.h"

Game::Game(){

}

void Game::init(SDL_Renderer* r){
	player.init(r);

	renderer = r;

	debug = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 30);

	Object obj;
	obj.init(renderer, 2, 0, 100, 100);
}

void Game::draw(){
	int i = 0;
	int j = 0;
	ObjectNode *ptr = objects;
	while (ptr != NULL){
		if (ptr->o.isDead())
			j++;
		ptr->o.draw();
		ptr = ptr->next;
		i++;
	}

	//Player on top
	player.draw();
	
	renderColorText(renderer, debug, 0, 200, "Object count: " + to_string(i) + "\nDead: " + to_string(j), {0,255,0});
}

void Game::update(){
	u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

	player.update();
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

	if (kDown & KEY_X)
		addObject();
}

void Game::addObject(){
	Object obj;
	obj.init(renderer, 0, 3, player.getX(), player.getY());


	ObjectNode *o = new ObjectNode;
	o->o = obj;
	o->next = objects;

	objects = o;
}