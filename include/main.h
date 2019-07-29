#ifndef MAIN
#define MAIN

//State can be changed from certain children
#define TITL_STATE 0
#define MENU_STATE 1
#define GAME_STATE 2

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

using namespace std;

typedef struct 
{
	SDL_Texture * texture;
} 
image;

#endif