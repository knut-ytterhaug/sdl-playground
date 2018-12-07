#include <SDL/SDL.h>
#include "config.h"
#include "screen.h"

SDL_Surface *screen;

void screen_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	screen = SDL_SetVideoMode(X, Y, 32, SDL_SWSURFACE);
}

void screen_main(void)
{
	
}

void putpixel(Uint16 x, Uint16 y, Uint32 pixel)
{
	*((Uint8 *)screen->pixels + y * screen->pitch + x) = pixel;
}
