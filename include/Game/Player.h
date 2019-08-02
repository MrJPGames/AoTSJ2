#ifndef CLASS_PLAYER
#define CLASS_PLAYER

#define UPGRADE_COUNT 1

#include <switch.h>
#include "GFX.h"
#include "main.h"

class Player{
	public:
		Player();
		void init(SDL_Renderer* renderer);
		void update();
		void draw();
		float getX();
		float getY();
		float getAim();
	private:
		void updateMovement();
		void updateAim();

		SDL_Renderer* renderer;
		float x = 960, y = 540, dx=0, dy=0, playerSpeed = 12, angle = 0;
		int upgrades[UPGRADE_COUNT];
		JoystickPosition jPosL, jPosR;
		image sprite;
		SDL_Surface* surface;
		TTF_Font* debug;
};

#endif