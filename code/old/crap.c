#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define X 1280
#define Y 1024
#define XC X/2
#define YC Y/2

struct ck 
{
	int x;
	int y;
	int r;
};

struct square
{
	int x;
	int y;
	int w;
	int h;
	int color;
};

typedef struct ck CK;
typedef CK *CIRCLE;

typedef struct square SQ;
typedef SQ *SQUARE;

int circle(int x, int y, struct ck *c)
{
	return sqrt(((x-c->r-(c->x-c->r))*(x-c->r-(c->x-c->r)))+((y-c->r-(c->y-c->r))*(y-c->r-(c->y-c->r))));
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
	int radius=50;
	CIRCLE knut[4];
	SQUARE box;

	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(X,Y,32,SDL_SWSURFACE);
	SDL_LockSurface(screen);
	
	box = malloc(sizeof(SQ));
	box->x = 100;
	box->y = 100;
	box->w = 100;
	box->h = 100;
	box->color = SDL_MapRGB(screen->format, 0, 128, 128);

	knut[0] = malloc(sizeof(CK));
	knut[0]->x = 500;
	knut[0]->y = 200;
	knut[0]->r = 50;
	knut[1] = malloc(sizeof(CK));
	knut[1]->x = 450;
	knut[1]->y = 175;
	knut[1]->r = 50;
	knut[2] = malloc(sizeof(CK));
	knut[2]->x = 450;
	knut[2]->y = 200;
	knut[2]->r = 50;
	knut[3] = malloc(sizeof(CK));
	knut[3]->x = 500;
	knut[3]->y = 200;
	knut[3]->r = 50;

	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	atexit(SDL_Quit);

	color = SDL_MapRGB(screen->format, 255, 255, 255);
	for(x = 0; x < X; x++)
	{
		p = (Uint8 *)screen->pixels + YC * screen->pitch + x * 4;
		*(Uint32 *)p = color;
	}
	for(x = 0; x < 50; x++)
	{
		for(y = 0; y < YC/200; y++)
		{
			p = (Uint8 *)screen->pixels + (YC-(200*(y))) * screen->pitch + ((XC-25)+x) * 4;
			*(Uint32 *)p = color;
			p = (Uint8 *)screen->pixels + (YC+(200*(y))) * screen->pitch + ((XC-25)+x) * 4;
			*(Uint32 *)p = color;
		}
	}
	for(x = 0; x < Y; x++)
	{
		p = (Uint8 *)screen->pixels + x * screen->pitch + XC * 4;
		*(Uint32 *)p = color;
	}
	for(x = 0; x < 20; x++)
	{
		for(y = 0; y < XC/90; y++)
		{
			p = (Uint8 *)screen->pixels + ((YC-10)+x) * screen->pitch + (XC+(90*(y+1))) * 4;
			*(Uint32 *)p = color;
			p = (Uint8 *)screen->pixels + ((YC-10)+x) * screen->pitch + (XC-(90*(y+1))) * 4;
			*(Uint32 *)p = color;
		}
	}

	i = 0;

	while(SDL_PollEvent(NULL)==0)
	{
		for(x = 0; x < X; x++)
		{
			color = SDL_MapRGB(screen->format, 0, 255, 0);
			color2 = SDL_MapRGB(screen->format, 0, 0, 255);

			y = sinius(x, 1);
			p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
			*(Uint32 *)p = color;
			
			y = sinius(x, 0.5);
			p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
			*(Uint32 *)p = color;

			y = sinius(x, 0.25);
			p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
			*(Uint32 *)p = color;

			y = sinius(x, 0.125);
			p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
			*(Uint32 *)p = color;

			y = sinius(x, 0.0625);
			p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
			*(Uint32 *)p = color;

			if(((YC+((((x-(i))-XC)*0.1)*(((x-(i))-XC)*0.1))*-1)+50) > 0)
			{
				y = (YC+((((x-(i))-XC)*0.1)*(((x-(i))-XC)*0.1))*-1)+50;
				p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
				*(Uint32 *)p = color2;
			}
			if( (((YC+(((x-XC)*0.1)*((x-XC)*0.1)*((x-XC)*0.1))*-1)) > 0) && (((YC+(((x-XC)*0.1)*((x-XC)*0.1)*((x-XC)*0.1))*-1)) < 600) )
			{
				y = (YC+(((x-XC)*0.1)*((x-XC)*0.1)*((x-XC)*0.1))*-1);
				p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
				*(Uint32 *)p = color2;
			}
			if( (sqrt(((x-radius)*(x-radius))+(((( sqrt( ((radius)*(radius))-(x*x) )+YC ))-radius)*(( sqrt( ((radius)*(radius))-(x*x) )+YC )-radius)))) < radius )
			{
				y = ( sqrt( ((radius)*(radius))-(x*x) )+YC );
				p = (Uint8 *)screen->pixels + y * screen->pitch + (x+XC+100) * 4;
				*(Uint32 *)p = color2;
			}
		}
		color2 = SDL_MapRGB(screen->format, 255, 0, 0);
		for(y = 0; y < Y; y++)
		{
			for(x = 0; x < X; x++)
			{
				if( (y < ((YC+(((x-XC)*0.1)*((x-XC)*0.1))*-1)+50) ) && (y > sin((x-XC)*M_PI/180)*-200+YC) && (y < (sin((x-XC)*M_PI/180)*-200)*0.5+YC) )
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
					*(Uint32 *)p = color2;
				}
				if( y < sinius(x, 0.125) && (y > sinius(x, 0.25)) )
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + (x) * 4;
					*(Uint32 *)p = color2;
				}
				if(circle(x, y, knut[0]) < knut[0]->r)
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = color;
				}
				if(circle(x, y, knut[1]) < knut[1]->r)
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = color;
				}
				if(circle(x, y, knut[2]) < knut[2]->r)
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = color;
				}
				if( (circle(x, y, knut[2]) < knut[2]->r) && (circle(x, y, knut[1]) < knut[1]->r) )
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = color2;
				}
				if( (circle(x, y, knut[2]) < knut[2]->r) && (circle(x, y, knut[0]) < knut[0]->r) )
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = color2;
				}
				if( (circle(x, y, knut[0]) < knut[0]->r) && (circle(x, y, knut[1]) < knut[1]->r) )
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = color2;
				}
				if( (circle(x, y, knut[0]) < knut[0]->r) && (circle(x, y, knut[1]) < knut[1]->r) && (circle(x, y, knut[2]) < knut[2]->r) )
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 200, 64, 64);
				}
			}
		}

		SDL_Flip(screen);
	}

	return 0;
}
