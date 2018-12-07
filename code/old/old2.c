#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	SDL_Surface *screen;
	Uint8 *p;
	Uint16 pixel;
	int x,y=0,f=0,i;
	double r[6], R[6];

	srand(time(NULL));
	for(i = 0; i < 6; i++)
		r[i] = ((double)(rand()%1000+1))/300000;
	for(i = 0; i < 6; i++)
		R[i] = ((double)(rand()%1000+1))/5000;

	double Fsin1[2000], Fsin2[2000], Fsin3[2000];

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(800,600,16,SDL_SWSURFACE);
	SDL_LockSurface(screen);

	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	atexit(SDL_Quit);

	for(i = 0; i < 2000; i++)
	{
		Fsin1[i] = sin(i/45)*63;
		Fsin2[i] = sin(i/35)*75;
		Fsin3[i] = sin(i/75)*92;
	}

	while(SDL_PollEvent(NULL)==0)
	{
		f++;
		for(y = 0; y < 600; y++)
		{
			for(x = 0; x < 800; x++)
			{
				pixel = SDL_MapRGB(screen->format, Fsin1[x+f], Fsin2[x+y-f], Fsin3[y-(int)(Fsin1[x-y])+f]);
				p = (Uint8 *)screen->pixels + y * screen->pitch + x * 2;
				*(Uint16 *)p = pixel;
			}
		}
		SDL_Flip(screen);
	}
	

	return 0;
}
