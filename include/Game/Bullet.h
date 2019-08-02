#ifndef CLASS_BULLET
#define CLASS_BULLET

#include "GFX.h"
#include "main.h"

class Bullet{
    public:
        Bullet();
        void init(SDL_Renderer* renderer, SDL_Texture* texture, float d, float s, float x, float y);
        void update();
        void draw();
        bool isDead();
		float getX();
		float getY();
		float getSize();
        void kill();
    private:
        bool alive = true;
        SDL_Renderer* renderer;
        image sprite;
        float x=0, y=0;
        float speed = 10;
        float direction = 0;
};

#endif