#include "Game/Game.h"

Game::Game(){

}

void Game::init(SDL_Renderer* r, TextureManager* t, AudioPlayer* mp){
	srand(time(0));

	player.init(r);

	renderer = r;

	font = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 45);

	textureManager = t;

	spawnTimer = EASY_TIMER_MAX;
	maxSpawnTimer = EASY_TIMER_MAX;

	audioPlayer = mp;
	audioPlayer->playMusic("romfs:/assets/music/placeholder.mp3");
}

void Game::draw(){
	drawObjects();
	drawBullets();

	//Player on top
	player.draw();

	drawHUD();

	if (objects != NULL)
		renderColorText(renderer, font, 40, 200, "Object size: " + to_string(objects->o.getSize()), {0, 255, 0});
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

void Game::drawHUD(){
	renderColorText(renderer, font, 40, 40, "Score: " + to_string(score) + "\nLives: " + to_string(player.getLives()), {255,255,255});
}

void Game::update(){
	u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
	u32 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

	player.update();
	updateObjects();
	updateBullets();
	checkObjectBulletCollision();
	//checkObjectPlayerCollision();

	//Object spawning logic
	spawnTimer--;
	if (spawnTimer <= 0){
		maxSpawnTimer -= EASY_TIMER_DEC;
		if (maxSpawnTimer < EASY_TIMER_MIN){
			maxSpawnTimer = EASY_TIMER_MIN;
		}
		spawnTimer = maxSpawnTimer;
		addObject();
	}

	//Shooting logic
	if (kDown & KEY_ZR){
		shootTimer = 0;
		addBullet();
	}
	shootTimer++;
	if (kHeld & KEY_ZR && (shootTimer % SHOOT_SPEED) == 0)
		addBullet();
}

void Game::checkObjectBulletCollision(){
	ObjectNode *ptr = objects;
	while (ptr != NULL){
		float ox = ptr->o.getX();
		float oy = ptr->o.getY();
		float os = ptr->o.getSize();

		BulletNode *bPtr = bullets;
		while (bPtr != NULL){
			float bx = bPtr->b.getX();
			float by = bPtr->b.getY();
			float bs = bPtr->b.getSize();
			if ((ox-bx) * (ox-bx) + (oy-by) * (oy-by) < (os+bs) * (os+bs)){
				bPtr->b.kill();
				ptr->o.kill();
				//TODO: Spawn explosion fx
				audioPlayer->playWAV("romfs:/assets/sfx/explosion.wav");
				score += 1000;
				bPtr = NULL;
				break;
			}else{
				bPtr = bPtr->next;
			}
		}
		ptr = ptr->next;
	}
}

void Game::updateObjects(){
	ObjectNode *ptr = objects;
	ObjectNode *prev = NULL;
	while (ptr != NULL){
		ptr->o.update();
		if (ptr->o.isDead()){
			ObjectNode *next = ptr->next;
			delete ptr;
			if (prev != NULL)
				prev->next = next;
			else
				objects = next;
			ptr = next;
		}else{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

void Game::updateBullets(){
	BulletNode *ptr = bullets;
	BulletNode *prev = NULL;
	while (ptr != NULL){
		ptr->b.update();
		if (ptr->b.isDead()){
			BulletNode *next = ptr->next;
			delete ptr;
			if (prev != NULL)
				prev->next = next;
			else
				bullets = next;
			ptr = next;
		}else{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

void Game::addObject(){
	float x, y;
	switch(rand() % 4){
		case 0:
			x = 0;
			y = rand() % 1080;
			break;
		case 1:
			x = rand() % 1920;
			y = 0;
		case 2:
			x = 1920;
			y = rand() % 1080;
			break;
		default:
			x = rand() % 1920;
			y = 1080;
	}
	Object obj;
	obj.init(renderer, textureManager, 3, x, y, player.getX(), player.getY());


	ObjectNode *o = new ObjectNode;
	o->o = obj;
	o->next = objects;

	objects = o;
}

void Game::addBullet(){
	Bullet obj;
	obj.init(renderer, textureManager, player.getAim(), 15, player.getX(), player.getY());


	BulletNode *b = new BulletNode;
	b->b = obj;
	b->next = bullets;

	bullets = b;

	audioPlayer->playWAV("romfs:/assets/sfx/shoot.wav");
}