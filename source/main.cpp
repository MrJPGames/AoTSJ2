#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_TTF.h>
#include "GFX.h"
#include "TextureManager.h"
#include "Game/Game.h"
#include "main.h"

//Sets the current mode (state) of the game
int mode = TITL_STATE;

touchPosition Stylus;
u32 kDown;

image background;


SDL_Window *    window;
SDL_Renderer *  renderer;
SDL_Surface *   surface;

TTF_Font* font;
TTF_Font* bigFont;

Game game;

TextureManager tm;

void draw(){
	SDL_RenderClear(renderer);
	renderTexture(renderer, background, 0, 0);
	game.draw();
	/*
	switch(mode){
		default:
			renderText(renderer, font, 0, 0, "Invalid mode encountered! Mode id: " + to_string(mode));
			break;
	}
	*/
	SDL_RenderPresent(renderer);
}

void update(){
	hidScanInput();
	kDown = hidKeysDown(CONTROLLER_P1_AUTO);
	hidTouchRead(&Stylus, 0);

	game.update();
}


int main(int argc, char **argv)
{
	romfsInit();
	
	SDL_Init(SDL_INIT_EVERYTHING);
	// Initialize
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window = SDL_CreateWindow("Main-Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Set blend mode
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	surface = IMG_Load("romfs:/assets/backgrounds/space.png");
	background.texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	tm.init(renderer);

	game.init(renderer, &tm);

	font = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 48);
	bigFont = TTF_OpenFont("romfs:/fonts/OpenSans.ttf", 72);
	// Game loop:
	while (true)
	{
		update();
		draw();
		if (kDown & KEY_PLUS)
			break;
	}

	//On detruit la fenètre
	SDL_DestroyWindow(window);
	IMG_Quit();	
    TTF_CloseFont(font);
    TTF_CloseFont(bigFont);
	TTF_Quit();
	SDL_Quit();
	romfsExit();

	return EXIT_SUCCESS;
}
