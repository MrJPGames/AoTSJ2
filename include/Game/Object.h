#ifndef CLASS_OBJECT
#define CLASS_OBJECT

#include <switch.h>
#include "GFX.h"
#include "main.h"
#include "TextureManager.h"

class Object{
	public:
		Object();
		void init(SDL_Renderer* renderer, TextureManager* tm, float s, float x, float y, float tx, float ty);
		bool isDead();
		void update();
		void draw();
		float getX();
		float getY();
		float getSize();
		void kill();
	private:
		SDL_Renderer* renderer;
		float x = 960, y = 540, speed = 12, angle = 0, direction = 0;
		image sprite;
		SDL_Surface* surface;
		bool alive = true;
		float angle_change=0;
		float scale = 0;
		int radius = 0;
};

#endif