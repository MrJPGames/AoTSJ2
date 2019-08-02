#ifndef CLASS_GAME
#define CLASS_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_TTF.h>
#include "GFX.h"

#include "Game/Player.h"
#include "Game/Object.h"
#include "Game/Bullet.h"

using namespace std;

#define EASY_TIMER_MAX 60
#define EASY_TIMER_MIN 30
#define EASY_TIMER_DEC 2

#define SHOOT_SPEED 10

struct ObjectNode{
	Object o;
	ObjectNode *next;
};

struct BulletNode{
	Bullet b;
	BulletNode *next;
};

class Game{
	public:
		Game();
		void init(SDL_Renderer* r);
		void update();
		void draw();
	private:
		void checkObjectBulletCollision();
		void updateObjects();
		void updateBullets();
		void drawObjects();
		void drawBullets();
		void addObject();
		void addBullet();

		SDL_Renderer* renderer;
		SDL_Surface* surface;
		//FontManager fontManager;
		Player player;
		ObjectNode *objects = NULL;
		BulletNode *bullets = NULL;
		TTF_Font* debug;
		int spawnTimer = 0;
		int maxSpawnTimer = 0;
		
		int shootTimer = 0;

		image defaultObject;
		image defaultBullet;
};

#endif