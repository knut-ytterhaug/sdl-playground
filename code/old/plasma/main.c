#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define X 256
#define Y 256
#define XC X/2
#define YC Y/2

int main(void)
{
	SDL_Surface *screen;
	Uint8 *p;
	Uint16 pixel;
	int x,y=0,f=0;
	int color, color2;
	int radius=50;
	
	unsigned char i;

	unsigned char t[256];
	unsigned char s[256];
	unsigned char u[256];

	unsigned int b[800][600];

	screen = SDL_SetVideoMode(X,Y,32,SDL_SWSURFACE);
	SDL_LockSurface(screen);
	
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	atexit(SDL_Quit);

	color = SDL_MapRGB(screen->format, 255, 255, 255);

	for(x = 0; x < 64; x++)
	{
		t[x] = (int)(sin(((x+50)*M_PI)/180));
		t[x+64] = (int)(sin(((x+20)*M_PI)/180));
		t[x+128] = (int)(sin(((x+90)*M_PI)/180));
		t[x+192] = (int)(sin(((x+5)*M_PI)/180));

		s[x] = (int)(sin(((x-100)*M_PI)/180)*100);
		s[x+64] = (int)(sin(((x-100)*M_PI)/180)*100);
		s[x+128] = (int)(sin(((x-100)*M_PI)/180)*100);
		s[x+192] = (int)(sin(((x-100)*M_PI)/180)*100);

		u[x] = (int)(sin((x*x*M_PI)/180));
		u[x+64] = (int)(sin((x*x*M_PI)/180));
		u[x+128] = (int)(sin((x*x*M_PI)/180));
		u[x+192] = (int)(sin((x*x*M_PI)/180));
	}

	
	i = 0;
	while(SDL_PollEvent(NULL)==0)
	{
		i++;
		for(x = 0; x < X; x++)
		{
			for(y = 0; y < Y; y++)
			{
				p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
				*(Uint32 *)p = SDL_MapRGB(screen->format, t[x], (i*x*x), (y*x*i)/2);
			}
		}
		SDL_Flip(screen);
	}

	return 0;
}
