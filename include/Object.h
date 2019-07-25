#ifndef CLASS_OBJECT
#define CLASS_OBJECT

#include <switch.h>
#include "GFX.h"
#include "main.h"

class Object{
	public:
		Object();
		void init(SDL_Renderer* renderer, float d, float s);
		void update();
		void draw();
	private:
		SDL_Renderer* renderer;
		float x = 960, y = 540, speed = 12, angle = 0, direction = 0;
		image sprite;
		SDL_Surface* surface;
};

#endif