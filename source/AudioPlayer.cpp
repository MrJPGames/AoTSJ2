#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(){
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}

void AudioPlayer::loadMusic(string path){
    musicMap[path] = Mix_LoadMUS(path.c_str());
}

void AudioPlayer::playMusic(string path){
    Mix_PlayMusic( musicMap[path], -1 );
}

void AudioPlayer::loadWAV(string path){
    chunkMap[path] = Mix_LoadWAV(path.c_str());
}

void AudioPlayer::playWAV(string path){
    Mix_PlayChannel( -1, chunkMap[path], 0 );
}
