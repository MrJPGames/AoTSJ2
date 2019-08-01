#ifndef CLASS_GAME
#define CLASS_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_TTF.h>
#include "GFX.h"

#include "Player.h"
#include "Object.h"
#include "Bullet.h"

using namespace std;

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

		image defaultObject;
		image defaultBullet;
};

#endif