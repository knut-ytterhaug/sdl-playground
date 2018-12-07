#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#define X 1600
#define Y 1200

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
		Palette[x].g = x*2;
		Palette[x].b = x;
		Palette[x].r = 0;

		Palette[x+64].g = x*2+128;
		Palette[x+64].b = x+64;
		Palette[x+64].r = 0;
		
		Palette[x+128].g = 255;
		Palette[x+128].b = x+128;
		Palette[x+128].r = 0;

		Palette[x+192].g = 255;
		Palette[x+192].b = 128-(x*2);
		Palette[x+192].r = 0;

	}
	SDL_SetColors(screen, Palette, 0, 255);
	
	for(y = 0; y < Y; y++)
	{
		for(x = 0; x < X; x++)
		{
			buffer[y][x] = 0;
		}
	}

	int i = 0;
	
	while(SDL_PollEvent(NULL) == 0)
	{
		srand(SDL_GetTicks());
		char *p = screen->pixels;
		
		for(x = 0; x < X; x++)
		{
			i = i + rand()%256;
			buffer[Y-1][x] = 128 + (rand() % 128);
		}

		for(x = 0; x < 50; x++)
		{
          buffer[Y-50][x+200] = 128 + (rand() % 128);
		}

		for(y = 0; y < Y-1; y++)
		{
			for(x = 0; x < X; x++)
			{
				buffer[y][x] = (buffer[y+1][x-1] + buffer[y+1][x] + buffer[y+1][x+1] + buffer[y+2][x]) / 4.01;
				*(p++) = buffer[y][x];
			}
		}
		for(x = 0; x < X; x++)
			*(p++) = buffer[Y-1][x];

		SDL_UpdateRect(screen, 0, 0, 0, 0);
		i++;
	}

	return 0;
}
