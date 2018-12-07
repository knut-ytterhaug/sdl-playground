#include <stdio.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define X 800
#define Y 600

void drawline(int x, int y, int length, int dir, unsigned char buffer[Y][X]);
void putpixel(int x, int y, unsigned char color, unsigned char buffer[Y][X]);
void putline(int x1, int y1, int x2, int y2, unsigned char color, unsigned char buffer[Y][X]);
void drawtriangle(int x, int y, int size, int rot, unsigned char color, unsigned char buffer[Y][X]);
void drawpolygon(int x, int y, int size, int rot, int sides, unsigned char color, unsigned char buffer[Y][X]);

void drawline(int x1, int y1, int x2, int y2, unsigned char buffer[Y][X])
{
  int level;
  int xlength, ylength;
  double hyp;
  double angle;

  xlength = x1 - x2;
  ylength = y1 - y2;

  if (xlength < 0) xlength = xlength * -1;
  if (ylength < 0) ylength = ylength * -1;


  hyp = atan(xlength/ylength);
  angle = asin(ylength/hyp);

  level = 1+(int) (10.0*rand()/(RAND_MAX+1.0));

  if(level <= 5)
  {
    putline(x1, y1, x2, y2, 255, buffer);
  }
  else
  {
    putline(x1, y1, x1+(int) cos(angle)*(hyp/4), y1+(int) sin(angle)*(hyp/4), 255, buffer);
  }
}

void putpixel(int x, int y, unsigned char color, unsigned char buffer[Y][X])
{
  x=x%X;
  y=y%Y;
  if(x > -1 && x < X && y < Y && y > -1)
  {
	buffer[y][x] = color;
  }
}

void putline(int x1, int y1, int x2, int y2, unsigned char color, unsigned char buffer[Y][X])
{
  int x, y;

  int xlength, ylength;

  xlength = (x1 > x2) ? x1-x2 : x2-x1;
  ylength = (y1 > y2) ? y1-y2 : y2-y1;

  if (xlength > ylength)
    for(x = 0; x <= xlength; x++)
      putpixel(x1 + ((x1>x2) ? -x : +x), y1 + ((y1>y2) ? ylength*x/xlength*-1 : ylength*x/xlength), 100+(int) (100.0*rand()/(RAND_MAX+1.0)), buffer);
  else
    for(y = 0; y <= ylength; y++)
      putpixel(x1 + ((x1>x2) ? xlength*y/ylength*-1 : xlength*y/ylength), y1 + ((y1>y2) ? -y : +y), 100+(int) (100.0*rand()/(RAND_MAX+1.0)), buffer);
}

void drawpolygon(int x, int y, int size, int rot, int sides, unsigned char color, unsigned char buffer[Y][X])
{
  int i;

  int axn[sides];
  int ayn[sides];

  float radius = sqrt( (size/2) * (size/2) + (sqrt( (size * size) - (size/2)*(size/2))/3) * (sqrt( (size * size) - (size/2)*(size/2))/3));

  for(i = 0; i < sides; i++)
  {
    axn[i] = x+radius*cos((rot+360/sides*i)*M_PI/180);
    ayn[i] = y+radius*sin((rot+360/sides*i)*M_PI/180);
  }

  for(i = 0; i < sides-1; i++)
  {
    putline(axn[i], ayn[i], axn[i+1], ayn[i+1], color, buffer);
  }
  putline(axn[sides-1], ayn[sides-1], axn[0], ayn[0], color, buffer);
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

		drawpolygon(X-200+(i/3), Y-200, 100, i/10, 4, 200, buffer);
		drawpolygon(i, Y/2+(sin((i*100/360)*M_PI/180)*100), 150, i/2, 3, 200, buffer);
		drawpolygon(X-300, Y-250+(i/20), 200, i/10, 2+(i/100), 200, buffer);
		
//		for(x = 0; x < X; x++)
//		{
//			i = i + rand()%256;
//			buffer[Y-1][x] = 128 + (rand() % 128);
//		}

		for(y = 0; y < Y-2; y++)
		{
			for(x = 0; x < X; x++)
			{
				buffer[y][x] = (buffer[y+1][x-1] + buffer[y+1][x] + buffer[y+1][x+1] + buffer[y+2][x]) / 4.01;
				*(p++) = buffer[y][x];
			}
		}
//		for(x = 0; x < X; x++)
//			*(p++) = buffer[Y-1][x];

		SDL_UpdateRect(screen, 0, 0, 0, 0);
		i++;
	}

	return 0;
}
