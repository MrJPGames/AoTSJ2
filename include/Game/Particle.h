#ifndef CLASS_PARTICLE
#define CLASS_PARTICLE

#include "GFX.h"
#include "main.h"
#include "TextureManager.h"

class Particle{
    public:
        Particle();
        void init(SDL_Renderer* renderer, TextureManager* tm, string path, float sx, float sy, int duration, float direction, float speed, float startAlpha, float endAlpha, float startScale, float endScale, float angleSpeed);
        void init(SDL_Renderer* renderer, TextureManager* tm, string path, float sx, float sy, int duration,float startAlpha, float endAlpha, float startScale, float endScale, float angleSpeed);
        void init(SDL_Renderer* renderer, image i, SDL_Rect tRect, float sx, float sy, int duration,float startAlpha, float endAlpha, float startScale, float endScale, float angleSpeed);
        void update();
        void draw();
        bool isDead();
    private:
        SDL_Renderer* renderer;
        image sprite;
        float x=0, y=0;
        float speed = 0;
        float direction = 0;
        float angleSpeed = 0;
        int duration = 0;
        float startAlpha = 0;
        float endAlpha = 0;
        float startScale = 0;
        float endScale = 0;
        int timer = 0;
        float scale = 0;
        float angle = 0;
        float alpha = 0;
        SDL_Rect texRect = NULL;
};

#endif