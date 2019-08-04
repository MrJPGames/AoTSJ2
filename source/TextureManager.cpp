#include "TextureManager.h"

TextureManager::TextureManager(){}

void TextureManager::init(SDL_Renderer* r){
    renderer = r;
}

image TextureManager::getTexture(string path){
    if (textureMap.count(path) == 0){
        surface = IMG_Load(path.c_str());
        textureMap[path].texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return textureMap[path];
}

image TextureManager::getRandomTexture(string dir){
    string paths[100];
    int i=0;
    for (const auto & entry : fs::directory_iterator(dir))
        if (fs::is_regular_file(entry.path())){
            paths[i++] = entry.path();
        }
    
    return getTexture(paths[rand() % i]);
}

void TextureManager::preloadTexture(string path){
    if (textureMap.count(path) == 0){
        surface = IMG_Load(path.c_str());
        textureMap[path].texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void TextureManager::preloadDirectory(string dir){
    for (const auto & entry : fs::directory_iterator(dir))
        if (fs::is_regular_file(entry.path()))
            preloadTexture(entry.path());
}