#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define X 800
#define Y 600 

void drawline(int x, int y, int length, int dir, SDL_Surface *screen);
void putpixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen);
void putline(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen);
void drawtriangle(int x, int y, int size, int rot, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen);
void drawpolygon(int x, int y, int size, int rot, int sides, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen);

void drawline(int x1, int y1, int x2, int y2, SDL_Surface *screen)
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
    putline(x1, y1, x2, y2, 255, 255, 255, screen);
  }
  else
  {
    putline(x1, y1, x1+(int) cos(angle)*(hyp/4), y1+(int) sin(angle)*(hyp/4), 255, 255, 255, screen);
  }
}

void putpixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen)
{
  Uint8 *p;
  x=x%X;
  y=y%Y;
  if(x > -1 && x < X && y < Y && y > -1)
  {
    p = (Uint8 *)screen->pixels + y * screen->pitch + x * 4;
    *(Uint32 *)p = SDL_MapRGB(screen->format, r, g, b);
  }
}

void putline(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen)
{
  int x, y;

  int xlength, ylength;

  xlength = (x1 > x2) ? x1-x2 : x2-x1;
  ylength = (y1 > y2) ? y1-y2 : y2-y1;

  if (xlength > ylength)
    for(x = 0; x <= xlength; x++)
      putpixel(x1 + ((x1>x2) ? -x : +x), y1 + ((y1>y2) ? ylength*x/xlength*-1 : ylength*x/xlength), r, g, b, screen);
  else
    for(y = 0; y <= ylength; y++)
      putpixel(x1 + ((x1>x2) ? xlength*y/ylength*-1 : xlength*y/ylength), y1 + ((y1>y2) ? -y : +y), r, g, b, screen);
}

void drawtriangle(int x, int y, int size, int rot, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen)
{
  drawpolygon(x, y, size, rot, 3, r, g, b, screen);
}

void drawpentagon(int x, int y, int size, int rot, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen)
{
  int ax, ay, bx, by, cx, cy, dx, dy, ex, ey;

  float radius = sqrt( (size/2) * (size/2) + (sqrt( (size * size) - (size/2)*(size/2))/3) * (sqrt( (size * size) - (size/2)*(size/2))/3));

  ax = x+radius*cos(rot*M_PI/180);
  ay = y+radius*sin(rot*M_PI/180);
  bx = x+radius*cos((rot+72)*M_PI/180);
  by = y+radius*sin((rot+72)*M_PI/180);
  cx = x+radius*cos((rot+144)*M_PI/180);
  cy = y+radius*sin((rot+144)*M_PI/180);
  dx = x+radius*cos((rot+216)*M_PI/180);
  dy = y+radius*sin((rot+216)*M_PI/180);
  ex = x+radius*cos((rot+288)*M_PI/180);
  ey = y+radius*sin((rot+288)*M_PI/180);

  putline(ax, ay, bx, by, r, g, b, screen);
  putline(bx, by, cx, cy, r, g, b, screen);
  putline(cx, cy, dx, dy, r, g, b, screen);
  putline(dx, dy, ex, ey, r, g, b, screen);
  putline(ex, ey, ax, ay, r, g, b, screen);
}

void drawpolygon(int x, int y, int size, int rot, int sides, unsigned char r, unsigned char g, unsigned char b, SDL_Surface *screen)
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
    putline(axn[i], ayn[i], axn[i+1], ayn[i+1], r, g, b, screen);
  }
  putline(axn[sides-1], ayn[sides-1], axn[0], ayn[0], r, g, b, screen);
}

int main(void)
{
	SDL_Surface *screen;
	int x, y;
	int color;
	
	int i;

	screen = SDL_SetVideoMode(X,Y,32,SDL_SWSURFACE);
	SDL_LockSurface(screen);
	
	SDL_EventState(SDL_ACTIVEEVENT, SDL_IGNORE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	atexit(SDL_Quit);

	color = SDL_MapRGB(screen->format, 255, 255, 255);

	i = 2;


  int t = 0;

	while(SDL_PollEvent(NULL)==0)
	{

		for(x = 0; x < X; x++)
		{
			for(y = 0; y < Y; y++)
			{
			  putpixel(x, y, 0, 0, 0, screen);
			}
		}
		
//		drawline(100, 100, 200, 200, screen);
		drawtriangle(i, 300+(sin((i*100/360)*M_PI/180)*100), 150, i, 255+i, 255-i, 0, screen);
		drawtriangle(200, 200, 150, i, 255+i, 255-i, 0, screen);
		drawtriangle(200, 200, 100, 90+i, 255+i, 255-i, 0, screen);
		drawtriangle(200, 200, 10, 90+i, 255+i, 255-i, 0, screen);
		drawtriangle(200, 200, 120, 90-i*2, 255-i, 255-i, 0, screen);
		drawtriangle(200+i, 200, 80, 90-i, 255+i, 255-i, 0, screen);
		drawpolygon(200+i, Y/4*3, 10+i, 90, 3, 255+i, 255-i, 0, screen);
		drawpentagon(i, 500+(sin((i*100/360)*M_PI/180)*100), 150, i, 255+i, 255-i, 0, screen);
		drawpolygon(X/2, Y/2, Y*0.8, 10+i, 4, 255+i, 255-i, 0, screen);
		drawpolygon(X/2, Y/2, Y*0.8, 10+i, 10, 255+i, 255-i, 0, screen);

		for(t = 0; t < 255; t=t+15)
		  drawtriangle(200, 200, 1+t, 90-i*2, 128+(t*10), 255-i, 0, screen);

//		drawline(0, Y-1, X, 2, screen);
//		drawline(0, YC, X, 6, screen);
		
		i++;

//		if (i == 15) i = 2;

		SDL_Flip(screen);
//		usleep(500000);
	}

	return 0;
}
