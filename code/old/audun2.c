#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.141592654
#endif
#define xw 320
#define yw 200

SDL_Color 	*Palette;
time_t 		start, 
		stop;
long int 	frames = 0;

int FilterEvents(const SDL_Event *event)
{
	if (event->type == SDL_QUIT) {
		stop = time(NULL);
		printf("Fps: %f\n", 
				(double)frames/(stop-start));
		exit(0);
	}
	return 1;
}	

void initpalette(SDL_Surface *dst, int currenttime) 
{
	int 	x;
	static int 	ltime;
	
	/* No need to change it everytime */
	if (abs(ltime - currenttime) < 5)
		return;
	Palette = (SDL_Color *)malloc(256*sizeof(SDL_Color));
	for (x = 0; x<256; x++) {
		Palette[x].r =  (unsigned char)((32 + 31 * 
					cos( x * M_PI / 128 + 
						(double)currenttime/74 ))* 4);
		Palette[x].g =  (unsigned char)((32 + 31 * 
					sin( x * M_PI / 128 + 
					(double)currenttime/63 )) * 4);
		Palette[x].b = (unsigned char)((32 - 31 * 
					cos( x * M_PI / 128 + 
					(double)currenttime/81 )) * 4);
	}
	SDL_SetColors(dst, Palette, 0, 256);
	ltime = currenttime;
}	

void usage() 
{
	printf("Usage plasma [-f(ullscreen)]\n");
	printf("Note: to be able to run this in fullscreen you'll "
				"need a modeline for 320x200\n");
	exit(1);
}

void setuptables( unsigned char *table1, unsigned char *table2) 
{
	int 	i, 
		j, 
		dst = 0;
		
	for (j=0; j<400; j++) {
		for (i=0; i<640; i++) {
			table1[dst] = (unsigned char) (64 + 63 * 
				      ( sin ((double)hypot(200-j, 320-i) /16)));
			table2[dst] = (unsigned char) (64 + 63 * 
					sin((float)i/(37+15*cos((float)j/74))) *
					cos((float)j/(31+11*sin((float)i/57))));
			dst++;	
		}
	}
}	

int main (int argc, char *argv[]) 
{
	SDL_Surface *screen;
int		fullscreen = 0, 
		currenttime, x, y, x1, x2, x3, y1, y2, y3;
	unsigned char 	table[1024000], 
			table2[1024000], 
			line[500], 
			*lptr, 
			*ptr[4];
	SDL_Event 	event;

	for (x = 1; x < argc; x++) {
		if(strcmp(argv[x], "-h") == 0) 
			usage();
		if(strcmp(argv[x], "-f") == 0) {
			fullscreen = 1;
		}
	}	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initiate video - aborting now!\n");
		return 1;
	}
	atexit(SDL_Quit);
	SDL_SetEventFilter(FilterEvents);
	
	if (fullscreen)
		screen = SDL_SetVideoMode(xw, yw, 8, 
				SDL_HWSURFACE|SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(xw, yw, 8, 
				SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_ShowCursor(0);
	setuptables(table, table2);
	start = time(NULL);
	while (1) {
		unsigned char *p = screen->pixels;
		double deg;
		currenttime = SDL_GetTicks() >> 2;
		initpalette(screen, currenttime);	
		frames++;
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				stop = time(NULL);
				printf("Fps: %f Coded by: Audun Hove\n", 
						(double)frames/(stop-start));
				return 1;
			}
		}
		x1 = 160 + (int)(159.0f * cos((double)currenttime/97));
       		x2 = 160 + (int)(159.0f * sin((double)-currenttime/114));
       		x3 = 160 + (int)(159.0f * sin((double)-currenttime/137));
       		y1 = 100 + (int)(99.0f * sin((double)currenttime/123));
       		y2 = 100 + (int)(99.0f * cos((double)-currenttime/75));
       		y3 = 100 + (int)(99.0f * cos((double)-currenttime/108));
             	ptr[0] = table + y1*640+x1;
		ptr[1] = table2 + y2*640+x2;
		ptr[2] = table2 + y3*640+x3; 	
		for (y = 0; y < yw; y++) {
			for (x = 0; x < xw;  x++) { 
				*(p++) = (unsigned char )(*ptr[0] + 
						*ptr[1] + *ptr[2]);
				ptr[0]++; ptr[1]++; ptr[2]++;
		 	}
			ptr[0]+=320; ptr[1]+=320; ptr[2]+=320;
		}
		SDL_Flip(screen);
		usleep(10);
	}		
	return 0;
}
