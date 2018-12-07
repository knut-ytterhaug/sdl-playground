#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	SDL_Surface *screen;
	Uint8 *p;
	Uint16 pixel;
	int x,y=0,f=0, i=0;
	int c;
	SDL_Color cl[16];

	srand(time(NULL));
	for(i = 0; i < 256; i++)
	{
		cl[i].r = rand()%1000+1;
		cl[i].g = rand()%1000+1;
		cl[i].b = rand()%1000+1;
	}
	
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(800,600,8,SDL_SWSURFACE);
	SDL_SetColors(screen, cl, 0, 256);
	SDL_LockSurface(screen);

	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	atexit(SDL_Quit);

	for(x = 0; x < 800; x++)
	{
		p = (Uint8 *)screen->pixels + 300 * screen->pitch + x;
		*(Uint16 *)p = 8;
	}
	for(x = 0; x < 600; x++)
	{
		p = (Uint8 *)screen->pixels + x * screen->pitch + 400;
		*(Uint16 *)p = 8;
	}

	for(x = 0; x < 800; x++)
	{
		y = sin((x-400)*M_PI/180)*100+300;
		p = (Uint8 *)screen->pixels + y * screen->pitch + x;
		*(Uint16 *)p = 2;
	}

	i=0;

	c = 100;
	while(SDL_PollEvent(NULL)==0)
	{
		for(y = 0; y < 600; y++)
		{
			for(x = 0; x < 800; x++)
			{
				if(sqrt(((x-c)*(x-c))+((y-c)*(y-c))) < c)
				{
					p = (Uint8 *)screen->pixels + (y) * screen->pitch + x;
					*(Uint16 *)p = sqrt(((x-c)*(x-c))+((y-c)*(y-c)))*sqrt(((x-c)*(x-c))+((y-c)*(y-c)))-(sqrt(((x-c)*(x-c))+((y-c)*(y-c))))-i;
				}
			}
		}
		i++;
		SDL_Flip(screen);
	}

	return 0;
}
