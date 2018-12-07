#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define X 320
#define Y 200

void putpixel(SDL_Surface *screen, int y, int x, int r, int g, int b)
{
	Uint16 pixel;
	Uint8 *p;

	if(!(y > Y || y < 0 || x < 0 || x > X))
	{
		pixel = SDL_MapRGB(screen->format, r, g, b);
		p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
		*(Uint32 *)p = pixel;
	}
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

	int buffer[X][Y];

	int i, x, y;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	screen = SDL_SetVideoMode(X, Y, 32, SDL_SWSURFACE);

	for(y = 0; y < Y; y++)
	{
		for(x = 0; x < X; x++)
		{
			buffer[y][x] = 0;
		}
	}

	buffer[Y-1][10] = 255;

	while(SDL_PollEvent(NULL) == 0)
	{
		srand(time(NULL));

		buffer[Y-1][10] = rand()%256;
		buffer[Y-1][50] = rand()%256;
		buffer[Y-1][15] = rand()%256;
		buffer[Y-1][100] = rand()%256;
		
		for(y = 1; y < Y-1; y++)
		{
			for(x = 1; x < X-1; x++)
			{
				buffer[y][x] = (buffer[y+1][x-1] + buffer[y+1][x] + buffer[y+1][x+1] + buffer[y+2][x])/4;
			}
		}

		for(y = 0; y < Y; y++)
		{
			for(x = 0; x < X; x++)
			{
				putpixel(screen, y, x, buffer[y][x], buffer[y][x], buffer[y][x]);
			}
		}
		
		SDL_Flip(screen);
	}

	return 0;
}
