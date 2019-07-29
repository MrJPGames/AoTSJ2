#ifndef CLASS_OBJECT
#define CLASS_OBJECT

#include <switch.h>
#include "GFX.h"
#include "main.h"

class Object{
	public:
		Object();
		void init(SDL_Renderer* renderer, SDL_Texture* texture, float d, float s, float x, float y);
		bool isDead();
		void update();
		void draw();
	private:
		SDL_Renderer* renderer;
		float x = 960, y = 540, speed = 12, angle = 0, direction = 0;
		image sprite;
		SDL_Surface* surface;
		bool alive = true;
};

#endif