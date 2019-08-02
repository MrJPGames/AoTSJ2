#ifndef GFX_H
#define GFX_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_TTF.h>
#include <string>

typedef struct {
	SDL_Texture * texture;
}image;

using namespace std;

void renderTexture(SDL_Renderer* renderer, image tex, int destX, int destY);
void renderTextureRotated(SDL_Renderer* renderer, image tex, int destX, int destY, double rotation);
void renderTextureScaled(SDL_Renderer* renderer, image tex, int destX, int destY, double scale);
void renderTextureScaledRotated(SDL_Renderer* renderer, image tex, int destX, int destY, double scale, double rotation);
void renderTextureCentered(SDL_Renderer* renderer, image tex, int x, int y);
void renderText(SDL_Renderer* renderer, TTF_Font* font, int x, int y, string s);
void renderColorText(SDL_Renderer* renderer, TTF_Font* font, int x, int y, string s, SDL_Color c);
void renderFadeOverlay(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void renderTextCentered(SDL_Renderer* renderer, TTF_Font* font, int x, int y, string s);
void renderColorTextCentered(SDL_Renderer* renderer, TTF_Font* font, int x, int y, string s, SDL_Color c);

#endif