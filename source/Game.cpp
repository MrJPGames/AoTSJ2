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
}

void Game::draw(){
	int i = 0;
	ObjectNode *ptr = objects;
	while (ptr != NULL){
		ptr->o.draw();
		ptr = ptr->next;
		i++;
	}

	//Player on top
	player.draw();
	
	renderColorText(renderer, debug, 0, 200, "Object count: " + to_string(i), {0,255,0});
}

void Game::update(){
	u32 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

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

	if (kHeld & KEY_X)
		addObject();
}

void Game::addObject(){
	Object obj;
	obj.init(renderer, defaultObject.texture, 0, 3, player.getX(), player.getY());


	ObjectNode *o = new ObjectNode;
	o->o = obj;
	o->next = objects;

	objects = o;
}