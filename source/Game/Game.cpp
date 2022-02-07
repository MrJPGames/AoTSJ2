#include "Game/Game.h"

Game::Game(){
}

void Game::init(SDL_Renderer* r, TextureManager* t, AudioPlayer* mp, PadState* padPtr){
	srand(time(0));

	player.init(r, padPtr);

	renderer = r;

	font = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 45);

	textureManager = t;

	spawnTimer = EASY_TIMER_MAX;
	maxSpawnTimer = EASY_TIMER_MAX;

	audioPlayer = mp;
	audioPlayer->playMusic("romfs:/assets/music/placeholder.mp3");
	
	pad = padPtr;
}

void Game::draw(){
	drawParticles();
	drawObjects();
	drawBullets();

	//Player on top
	player.draw();

	drawHUD();

	if (particles != NULL)
		renderColorText(renderer, font, 40, 200, "Particles exist", {0, 255, 0});
}

void Game::drawObjects(){
	ObjectNode *ptr = objects;
	while (ptr != NULL){
		ptr->o->draw();
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

void Game::drawParticles(){
	ParticleNode *ptr = particles;
	while(ptr != NULL){
		ptr->p.draw();
		ptr = ptr->next;
	}
}

void Game::drawHUD(){
	renderColorText(renderer, font, 40, 40, "Score: " + to_string(score) + "\nLives: " + to_string(player.getLives()), {255,255,255});
}

void Game::update(){
	u32 kDown = padGetButtonsDown(pad);
	u32 kHeld = padGetButtons(pad);

	player.update();
	updateObjects();
	updateBullets();
	updateParticles();
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
	if (kDown & HidNpadButton_ZR || kDown & HidNpadButton_ZL){
		shootTimer = 0;
		addBullet();
	}
	shootTimer++;
	if ((kHeld & HidNpadButton_ZR || kHeld & HidNpadButton_ZL) && (shootTimer % SHOOT_SPEED) == 0)
		addBullet();
}

void Game::checkObjectBulletCollision(){
	ObjectNode *ptr = objects;
	while (ptr != NULL){
		float ox = ptr->o->getX();
		float oy = ptr->o->getY();
		float os = ptr->o->getSize();

		BulletNode *bPtr = bullets;
		while (bPtr != NULL){
			float bx = bPtr->b.getX();
			float by = bPtr->b.getY();
			float bs = bPtr->b.getSize();
			if ((ox-bx) * (ox-bx) + (oy-by) * (oy-by) < (os+bs) * (os+bs)){
				objectExplodes(ptr->o);
				bPtr->b.kill();
				ptr->o->kill();
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

//Plays explosion sfx, creates particles associated with explosion
void Game::objectExplodes(Object* o){
	audioPlayer->playWAV("romfs:/assets/sfx/explosion.wav");

	image i = o->getTexture();
	int w, h;
    SDL_QueryTexture(i.texture, NULL, NULL, &w, &h);
	float s = o->getScale();
	float a = o->getAngle();

	for (int x = 0; x < 8; x++){
		for (int y=0; y<8; y++){
			SDL_Rect rect;
			rect.x = x*(w/8);
			rect.y = y*(h/8);
			rect.w = w/8;
			rect.h = h/8;

			int oX = o->getX();
			int oY = o->getY();
			int pX = oX-(s*w/2)+(x*(s*w/8)+(w/16)); //These do not take rotation of the sprite into account!
			int pY = oY-(s*h/2)+(y*(s*h/8)+(w/16));
			float partDir = atan2(pY-oY, pX-oX); //Direction from object to particle location
			int dx = pX - oX;
			int dy = pY - oY;
			float pointDist = sqrt(dx*dx+dy*dy);

			float positionAngle = partDir+o->getRadAngle();

			Particle part;
			part.init(renderer, //Renderer
			o->getTexture(), //texture (as image)
			rect, //srcRect (Rectangle defining area of textur to use)
			oX + pointDist*cos(positionAngle), //Start x
			oY + pointDist*sin(positionAngle), //Start y
			30, //Frame duration (60fps)
			positionAngle, //Moving direction (deg)
			s/3, //Moving speed (pixels per second)
			1, //Start alpha
			0, //End alpha
			s, //Start scale
			0, //End scale
			a, //Start angle
			5 //Angle speed (deg)
			);
			addParticle(part);
		}
	}
}

void Game::updateObjects(){
	ObjectNode *ptr = objects;
	ObjectNode *prev = NULL;
	while (ptr != NULL){
		ptr->o->update();
		if (ptr->o->isDead()){
			ObjectNode *next = ptr->next;
			delete ptr->o;
			delete ptr;
			if (prev != NULL)
				prev->next = next;
			else
				objects = next;
			ptr = next;
		}else{
			//If not dead, check if Object is of type SpecialObject
			if (typeid(*(ptr->o)) == typeid(SpecialObject)){
				Particle part;
		  		part.initDir(renderer, textureManager, "romfs:/assets/particles/rainbow_trail/", ptr->o->getX(),ptr->o->getY(), 30, (float)(rand()%360*PI/180.0f), (rand()%3+1), 2, 0, 16+(rand()%16), 0, rand() % 10);
				addParticle(part);
			}
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
			Particle obj;
			obj.init(renderer, textureManager, "romfs:/assets/particles/trail.png", ptr->b.getX(),ptr->b.getY(), 30, 1, 0, 4, 0, 2);
			addParticle(obj);
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

void Game::updateParticles(){
	ParticleNode *ptr = particles;
	ParticleNode *prev = NULL;
	while (ptr != NULL){
		ptr->p.update();
		if (ptr->p.isDead()){
			ParticleNode *next = ptr->next;
			delete ptr;
			if (prev != NULL)
				prev->next = next;
			else
				particles = next;
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
	Object* obj;
	if (rand() % 64 == 0){ //1 in 64
		obj = new SpecialObject;
	}else{
		obj = new Object;
	}
	obj->init(renderer, textureManager, 3, x, y, player.getX(), player.getY());


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

void Game::addParticle(Particle obj){
	ParticleNode *p = new ParticleNode;
	p->p = obj;
	p->next = particles;

	particles = p;
}
