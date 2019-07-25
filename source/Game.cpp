#include "Game.h"

Game::Game(){

}

void Game::init(SDL_Renderer* r){
	player.init(r);
}

void Game::draw(){
	player.draw();
	struct ObjectNode* ptr = objects;
	while (ptr != NULL){
		ptr->o.draw();
		ptr = ptr->ptr;
	}
}

void Game::update(){
	player.update();
	struct ObjectNode* ptr = objects;
	while (ptr != NULL){
		ptr.o.update();
		ptr = ptr.ptr;
	}
	addObject();
}

void Game::addObject(){
	Object obj;
	obj.init(renderer, 1, 3);


	struct ObjectNode* o;
	o.o = obj;
	o.ptr = objects;

	objects = o;
}