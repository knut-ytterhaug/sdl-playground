#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#define X 400
#define Y 300

void putpixel(SDL_Surface *screen, int y, int x, Uint16 pixel)
{
	Uint8 *p;

	p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
	*(Uint32 *)p = pixel;
}

void clearscreen(SDL_Surface *screen)
{
	int x, y;
	Uint16 pixel;
	Uint8 *p;

	for(y = 0; y < Y; y++)
	{
		for(x = 0; x < X; x++)
		{
			pixel = SDL_MapRGB(screen->format, 0, 0, 0); 
			p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
			*(Uint32 *)p = pixel;
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Surface *screen;

	int i, x, y;

	SDL_Color colors[256];

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	screen = SDL_SetVideoMode(X, Y, 8, SDL_SWSURFACE);
	
	for(i = 0; i < 64; i++)
	{
		colors[i].r = 0; 
		colors[i].g = 0;
		colors[i].b = x*3;

		colors[i+64].r = x*3;
		colors[i+64].g = 0;
		colors[i+64].b = 255-x*3;

		colors[i+128].r = 255-x*3;
		colors[i+128].g = x*3;
		colors[i+128].b = 0;

		colors[i+192].r = 0;
		colors[i+192].g = 255-x*3;
		colors[i+192].b = 0;
	}

	SDL_SetColors(screen, colors, 0, 255);

	int sinus[256];

	for(i = 0; i < 256; i++)
	{
		sinus[i] = sin(i*M_PI/180)*128+127;
	}

	unsigned char vptr, vptr2;
	unsigned char hptr, hptr2;
	
	while(SDL_PollEvent(NULL) == 0)
	{
		char *p = screen->pixels;

		i++;
		for(x = 0; x < X; x++)
		{
			for(y = 0; y < Y; y++)
			{
				*(p++) = sin(y); 
			}
		}
		SDL_Flip(screen);
	}

	while(SDL_PollEvent(NULL) == 0)
	{
		SDL_Flip(screen);
	}

	return 0;
}
