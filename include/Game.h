#ifndef CLASS_GAME
#define CLASS_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_TTF.h>
#include "GFX.h"

#include "Player.h"
#include "Object.h"

using namespace std;

struct ObjectNode{
	Object o;
	ObjectNode *next;
};

class Game{
	public:
		Game();
		void init(SDL_Renderer* r);
		void update();
		void draw();
		void addObject();
	private:
		SDL_Renderer* renderer;
		SDL_Surface* surface;
		//FontManager fontManager;
		Player player;
		struct ObjectNode* objects = NULL;
		TTF_Font* debug;

		image defaultObject;
};

#endif