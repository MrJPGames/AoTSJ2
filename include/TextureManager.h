#ifndef CLASS_TM
#define CLASS_TM

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_TTF.h>
#include <map>

#include "main.h"

using namespace std;

class TextureManager{
	public:
		TextureManager();
		void init(SDL_Renderer* r);
        image getTexture(string path);
	private:
        map<string, image> textureMap;
        SDL_Renderer* renderer;
		SDL_Surface* surface;
};

#endif