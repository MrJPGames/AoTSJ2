#ifndef CLASS_AudioPlayer
#define CLASS_AudioPlayer

#include <switch.h>
#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <map>

using namespace std;

class AudioPlayer{
	public:
		AudioPlayer();
        void loadMusic(string path);
        void playMusic(string path);
        void loadWAV(string path);
        void playWAV(string path);
	private:
        map<string, Mix_Music*> musicMap;
        map<string, Mix_Chunk*> chunkMap;
};

#endif