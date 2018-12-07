#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define X 1800
#define Y 1000
#define XC X/2
#define YC Y/2

void drawline(int x, int y, int length, int dir, SDL_Surface *screen);

void drawline(int x, int y, int length, int dir, SDL_Surface *screen)
{
	Uint8 *p;
	int i, j;
	int level;

	if(dir >= 8)
		dir = dir - 8;
	else if(dir < 0)
		dir = dir + 8;

	level = 1+(int) (10.0*rand()/(RAND_MAX+1.0));

	printf("%i, %i, %i, %i\n", x, y, length, dir);

	if(level <= 5)
	{
		switch(dir)
		{
			case 0:
				for(i = 0; i < length; i++)
				{
					if((i < length/4)||(y > ((length/4)+(length/2))))
					{
						p = (Uint8 *)screen->pixels + (y-i) * screen->pitch + x * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				break;
			case 1:
				for(i = 0; i < length/2; i++)
				{
					p = (Uint8 *)screen->pixels + (y-i) * screen->pitch + (x+i) * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}
				break;
			case 2:
				for(i = 0; i < length; i++)
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + (x+i) * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}
				break;
			case 3:
				for(i = 0; i < length/2; i++)
				{
					p = (Uint8 *)screen->pixels + (y+i) * screen->pitch + (x+i) * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}
				break;
			case 4:
				for(i = 0; i < length; i++)
				{
					p = (Uint8 *)screen->pixels + (y+i) * screen->pitch + x * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}
				break;
			case 5:
				for(i = 0; i < length/2; i++)
				{
					p = (Uint8 *)screen->pixels + (y+i) * screen->pitch + (x-i) * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}
				break;
			case 6:
				for(i = 0; i < length; i++)
				{
					p = (Uint8 *)screen->pixels + y * screen->pitch + (x-i) * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}
				break;
			case 7:
				for(i = 0; i < length/2; i++)
				{
					p = (Uint8 *)screen->pixels + (y-i) * screen->pitch + (x-i) * 4;
					*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
				}		
				break;
			default:
				break;
		}
	}
	else
	{
		switch(dir)
		{
			case 0:
				if (1+(int) (10.0*rand()/(RAND_MAX+1.0)) <= 0) {
					drawline(x, y, length/4, dir, screen);
				}
				else {
				for(i = 0; i < length; i++)
				{
					if((i <= length/4)||(i >= ((length/4)+(length/2))))
					{
						p = (Uint8 *)screen->pixels + (y-i) * screen->pitch + x * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				}
				drawline(x, (y-(length/4)), length/2, dir-1, screen);
				drawline((x-(length/4)), (y-(length/2)), length/2, dir+1, screen);
				break;
			case 1:
				for(i = 0; i < length/2; i++)
				{
					if((i <= length/8)||(i >= ((length/8)+(length/4))))
					{
						p = (Uint8 *)screen->pixels + (y-i) * screen->pitch + (x+i) * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline((x+(length/8)), (y-(length/8)), length/4, dir-1, screen);
				drawline((x+(length/8)), (y-((length/8)*3)), length/4, dir+1, screen);
				break;
			case 2:
				for(i = 0; i < length; i++)
				{
					if((i <= length/4)||(i >= ((length/4)+(length/2))))
					{
						p = (Uint8 *)screen->pixels + y * screen->pitch + (x+i) * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline((x+(length/4)), y, length/2, dir-1, screen);
				drawline((x+(length/2)), (y-(length/4)), length/2, dir+1, screen);

				break;
			case 3:
				for(i = 0; i < length/2; i++)
				{
					if((i <= length/8)||(i >= ((length/8)+(length/4))))
					{
						p = (Uint8 *)screen->pixels + (y+i) * screen->pitch + (x+i) * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline((x+(length/8)), (y+(length/8)), length/4, dir-1, screen);
				drawline((x+((length/8)*3)), (y+(length/8)), length/4, dir+1, screen);
				break;
			case 4:
				for(i = 0; i < length; i++)
				{
					if((i <= length/4)||(i >= ((length/4)+(length/2))))
					{
						p = (Uint8 *)screen->pixels + (y+i) * screen->pitch + x * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline(x, (y+(length/4)), length/2, dir-1, screen);
				drawline((x+(length/4)), (y+(length/2)), length/2, dir+1, screen);
				break;
			case 5:
				for(i = 0; i < length/2; i++)
				{
					if((i <= length/8)||(i >= ((length/8)+(length/4))))
					{
						p = (Uint8 *)screen->pixels + (y+i) * screen->pitch + (x-i) * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline((x-(length/8)), (y+(length/8)), length/4, dir-1, screen);
				drawline((x-(length/8)), (y+((length/8)*3)), length/4, dir+1, screen);
				break;
			case 6:
				for(i = 0; i < length; i++)
				{
					if((i <= length/4)||(i >= ((length/4)+(length/2))))
					{
						p = (Uint8 *)screen->pixels + y * screen->pitch + (x-i) * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline((x-(length/4)), y, length/2, dir-1, screen);
				drawline((x-(length/2)), (y+(length/4)), length/2, dir+1, screen);
				break;
			case 7:
				for(i = 0; i < length/2; i++)
				{
					if((i <= length/8)||(i >= ((length/8)+(length/4))))
					{
						p = (Uint8 *)screen->pixels + (y-i) * screen->pitch + (x-i) * 4;
						*(Uint32 *)p = SDL_MapRGB(screen->format, 255, 255, 255);
					}
				}
				drawline((x-(length/8)), (y-(length/8)), length/4, dir-1, screen);
				drawline((x-((length/8)*3)), (y-(length/8)), length/4, dir+1, screen);
				break;
			default:
				break;
		}
	}
}

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

	i = 0;
	while(SDL_PollEvent(NULL)==0)
	{
		for(x = 0; x < X; x++)
		{
			for(y = 0; y < Y; y++)
			{
				p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
				*(Uint32 *)p = SDL_MapRGB(screen->format, 0, 0, 0);
			}
		}
		
		drawline(0, YC, X, 2, screen);
		drawline(0, YC, X, 6, screen);
		drawline(100, 100, 100, 3, screen);
		drawline(100, 100, 100, 7, screen);
		drawline(100, 100, 100, 2, screen);
		drawline(100, 100, 100, 5, screen);
		drawline(X-100, 100, 100, 5, screen);
		drawline(X-100, 100, 100, 1, screen);
		drawline(X-100, Y-100, 100, 7, screen);
		drawline(X-100, Y-100, 100, 3, screen);
		drawline(100, Y-100, 100, 1, screen);
		drawline(100, Y-100, 100, 5, screen);
		
		i++;

		SDL_Flip(screen);
		sleep(1);
	}

	return 0;
}
