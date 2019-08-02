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
		int sign(int x);

		SDL_Renderer* renderer;
		float x = 960, y = 540, playerSpeed = 12, angle = 0;
		float vx = 0, vy = 0, gvx = 0, gvy = 0; //Velocity and goal velocity
		int upgrades[UPGRADE_COUNT];
		JoystickPosition jPosL, jPosR;
		image sprite;
		SDL_Surface* surface;
		TTF_Font* debug;
};

#endif