#ifndef CLASS_GAME
#define CLASS_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GFX.h"
#include "TextureManager.h"
#include "AudioPlayer.h"

#include "Game/Player.h"
#include "Game/Object.h"
#include "Game/SpecialObject.h"
#include "Game/Bullet.h"
#include "Game/Particle.h"

using namespace std;

#define EASY_TIMER_MAX 60
#define EASY_TIMER_MIN 30
#define EASY_TIMER_DEC 2

#define SHOOT_SPEED 10

struct ObjectNode{
	Object* o;
	ObjectNode *next;
};

struct BulletNode{
	Bullet b;
	BulletNode *next;
};

struct ParticleNode{
	Particle p;
	ParticleNode *next;
};

class Game{
	public:
		Game();
		void init(SDL_Renderer* r, TextureManager* t, AudioPlayer* mp, PadState* padPtr);
		void update();
		void draw();
	private:
		void checkObjectBulletCollision();
		void updateObjects();
		void updateBullets();
		void updateParticles();
		void drawObjects();
		void drawBullets();
		void drawParticles();
		void drawHUD();
		void addObject();
		void addBullet();
		void addParticle(Particle p);

		void objectExplodes(Object* o);

		SDL_Renderer* renderer;
		PadState* pad;
		//FontManager fontManager;
		Player player;
		ObjectNode *objects = NULL;
		BulletNode *bullets = NULL;
		ParticleNode *particles = NULL;
		TTF_Font* font;
		int spawnTimer = 0;
		int maxSpawnTimer = 0;
		
		int shootTimer = 0;

		int score = 0;

		TextureManager* textureManager;
		AudioPlayer* audioPlayer;
};

#endif
