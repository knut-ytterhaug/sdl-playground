#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "hsv.h"
#include "screen.h"
#define X 500
#define Y 500

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Color *Palette;
	
	int x, y;
	unsigned char buffer[Y][X];

	double cRe, cIm;
	double newRe, newIm, oldRe, oldIm;
	double zoom = 1, moveX = 0, moveY = 0;

	Uint16 color;

	int maxIterations = 300;

	cRe = -0.7;
	cIm = 0.27015;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	screen = SDL_SetVideoMode(X, Y, 32, SDL_SWSURFACE);

	Palette = (SDL_Color *)malloc(256*sizeof(SDL_Color));
	for(x = 0; x < 64; x++)
	{
		Palette[x].r = x*2;
		Palette[x].g = x;
		Palette[x].b = 0;

		Palette[x+64].r = x*2+128;
		Palette[x+64].g = x+64;
		Palette[x+64].b = 0;
		
		Palette[x+128].r = 255;
		Palette[x+128].g = x+128;
		Palette[x+128].b = 0;

		Palette[x+192].r = 255;
		Palette[x+192].g = 128-(x*2);
		Palette[x+192].b = 0;

	}
//	SDL_SetColors(screen, Palette, 0, 255);
	
	for(y = 0; y < Y; y++)
	{
		for(x = 0; x < X; x++)
		{
			buffer[y][x] = 0;
		}
	}

	int i,d;
	
	while(SDL_PollEvent(NULL) == 0)
	{
		printf("%d\n", d);
		char *p = screen->pixels;
		
		for(y = 0; y < Y-1; y++)
		{
			for(x = 0; x < X; x++)
			{
				newRe = 1.5 * (x - X / 2) / (0.5 * zoom * X) + moveX;
				newIm = (y - Y / 2) / (0.5 * zoom * Y) + moveY;

				for(i = 0; i < maxIterations; i++)
				{
					oldRe = newRe;
					oldIm = newIm;

					newRe = oldRe * oldRe - oldIm * oldIm + cRe;
					newIm = 2 * oldRe * oldIm * cIm;

					if((newRe * newRe + newIm * newIm) > 4) break;
				}
				
//				color = HSVtoRGB(i % 256, 100, 100 * (i < maxIterations));
//				color = SDL_MapRGB(screen->format, i % 256, 255, 255 * (i < maxIterations));
//				printf("%d\n", i % 256);
				
				*(p++) = color;
			}
		}
		d++;

		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	return 0;
}
