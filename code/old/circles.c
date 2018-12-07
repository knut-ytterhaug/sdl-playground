#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define X 800
#define Y 600
#define XC X/2
#define YC Y/2

struct circle
{
	int x;
	int y;
	int radius;
	int color;
};

struct square
{
	int x;
	int y;
	int w;
	int h;
	int color;
};

typedef struct circle CK;
typedef CK *CIRCLE;

typedef struct square SQ;
typedef SQ *SQUARE;

void draw_square(SDL_Surface *screen, struct square *sq)
{
	Uint8 *p;
	int x, y;
	for(y = 0; y < sq->h; y++)
	{
		for(x = 0; x < sq->w; x++)
		{
			p = (Uint8 *)screen->pixels + (sq->y+y) * screen->pitch + (sq->x+x) * 4;
			*(Uint32 *)p = sq->color;
		}
	}
}

void draw_circle(SDL_Surface *screen, struct circle *ck)
{
	Uint8 *p;
	int x, y;
	for(x = 0; x < (ck->radius*2); x++)
	{
		for(y = 0; y < (ck->radius*2); y++)
		{
			if( sqrt( ( (x-ck->radius) * (x-ck->radius) )+( (y-ck->radius) * (y-ck->radius) ) ) < ck->radius )
			{
				p = (Uint8 *)screen->pixels + ((y-ck->radius)+ck->y) * screen->pitch + ((x-ck->radius)+ck->x) * 4;
				*(Uint32 *)p = ck->color;
			}
		}
	}
}

int sinius(int x, double s)
{
	return (sin((x-XC)*M_PI/180)*-200)*s+YC;
}

int main(void)
{
	SDL_Surface *screen;
	Uint8 *p;
	Uint16 pixel;
	int x,y=0,f=0, i=0;
	int color, color2;
	SQUARE box;
	CIRCLE ck;

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(X,Y,32,SDL_SWSURFACE);
	SDL_LockSurface(screen);
	
	box = malloc(sizeof(SQ));
	box->x = 100;
	box->y = 100;
	box->w = 300;
	box->h = 100;
	box->color = SDL_MapRGB(screen->format, 0, 128, 128);

	ck = malloc(sizeof(CK));
	ck->x = 100;
	ck->y = 175;
	ck->radius = 50;
	ck->color = SDL_MapRGB(screen->format, 255, 0, 128);

	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	atexit(SDL_Quit);

	color = SDL_MapRGB(screen->format, 255, 255, 255);

	draw_circle(screen, ck);
	draw_square(screen, box);

	SDL_Flip(screen);
	
	while(SDL_PollEvent(NULL)==0)
	{
		for(i = 0; i < 10; i++)
		{
			ck->x = 50+(i*40);
			ck->y = 50+(i*30);
			ck->radius = 50+(i*10);
			ck->color = SDL_MapRGB(screen->format, i*25, (i*25)-150, i);
			draw_circle(screen, ck);
			SDL_Delay(500);
			SDL_Flip(screen);
		}
	}

	return 0;
}
