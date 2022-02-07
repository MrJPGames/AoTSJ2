#ifndef CLASS_TM
#define CLASS_TM

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>

#include "GFX.h"

namespace fs = std::filesystem;
using namespace std;

class TextureManager{
	public:
		TextureManager();
		void init(SDL_Renderer* r);
        image getTexture(string path);
		image getRandomTexture(string dir);
		void preloadTexture(string path);
		void preloadDirectory(string dir);
	private:
        map<string, image> textureMap;
        SDL_Renderer* renderer;
		SDL_Surface* surface;
};

#endif
