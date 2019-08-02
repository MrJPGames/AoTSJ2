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