#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#define X 320
#define Y 240

void putpixel(SDL_Surface *dst, Uint16 x, Uint16 y, Uint32 pixel)
{
	*((Uint8 *)dst->pixels + y * dst->pitch +x) = pixel;
}

int main(int argc, char *argv[])
{
	SDL_Surface *screen;
	SDL_Color *Palette;
	
	int x, y;
	unsigned char buffer[Y][X];

	SDL_Init(SDL_INIT_VIDEO);
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	screen = SDL_SetVideoMode(X, Y, 8, SDL_SWSURFACE);

	Palette = (SDL_Color *)malloc(256*sizeof(SDL_Color));
	for(x = 0; x < 64; x++)
	{
		Palette[x].r = 0;
		Palette[x].g = x;
		Palette[x].b = x*2;

		Palette[x+64].r = 0;
		Palette[x+64].g = x+64;
		Palette[x+64].b = x*2+128;
		
		Palette[x+128].r = 0;
		Palette[x+128].g = x+128;
		Palette[x+128].b = 255;

		Palette[x+192].r = 0;
		Palette[x+192].g = 128-(x*2);
		Palette[x+192].b = 255;

	}
	SDL_SetColors(screen, Palette, 0, 255);
	
	for(y = 0; y < Y; y++)
	{
		for(x = 0; x < X; x++)
		{
			buffer[y][x] = 0;
		}
	}

	while(SDL_PollEvent(NULL) == 0)
	{
		srand(SDL_GetTicks());
		char *p = screen->pixels;
		
		for(y = 0; y < 100; y++)
		{
			buffer[y+60][100] = 255;
			buffer[y+60][199] = 255;
		}
		for(x = 0; x < 100; x++)
		{
			buffer[60][x+100] = 255;
			buffer[160][x+100] = 255;
		}


		for(y = 0; y < 50; y++)
		{
			buffer[y+85][125] = 255;
			buffer[y+85][174] = 255;
		}
		for(x = 0; x < 50; x++)
		{
			buffer[85][x+125] = 255;
			buffer[135][x+125] = 255;
		}


		for(y = 0; y < Y; y++)
			for(x = 0; x < X; x++)
				*(p++) = buffer[y][x];

		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	return 0;
}
