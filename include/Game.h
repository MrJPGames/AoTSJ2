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
	Object o,
	ObjectNode* ptr
};

class Game{
	public:
		Game();
		void init(SDL_Renderer* r);
		void update();
		void draw();
	private:
		SDL_Renderer* renderer;
		//FontManager fontManager;
		Player player;
		struct ObjectNode* objects = NULL;
};

#endif