#include <SDL/SDL.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
SDL_Color *Palette;

// Woopsie noen har fikla med vinduet vårt
int FilterEvents(const SDL_Event *event){
	// Har de lukket det?
	if (event->type == SDL_QUIT) {
		exit(0);
	}
}	
#ifndef M_PI
#define M_PI 3.141592654
#endif
#define numcols 3
// Tegne prikk ting :)
void putpixel(SDL_Surface *dst, Uint16 x, Uint16 y, Uint32 pixel) {
		*((Uint8 *)dst->pixels + y * dst->pitch + x) = pixel;
}

// Setter opp paletten, vi går fra svart til blå,  fra rød til grønn, og fra grønn til svart
void initpalette(SDL_Surface *dst, int palmod) {
	int x;
	Palette = (SDL_Color *)malloc(256*sizeof(SDL_Color));
	
	if (palmod == 1) {
		for (x = 0; x<64; x++) {
			Palette[x].r = 0;
			Palette[x].g = 0;
			Palette[x].b = x * 3;

			Palette[x+64].r = x * 3;
			Palette[x+64].g = 0;
			Palette[x+64].b = 255 - x * 3;

			Palette[x+128].r = 255 - x * 3;
	 		Palette[x+128].g = x * 3;
			Palette[x+128].b = 0;

			Palette[x+128+64].r = 0;
			Palette[x+128+64].g = 255 - x * 3;
			Palette[x+128+64].b = 0;
		}
	}
	
	if (palmod == 2) {
		for (x = 0; x<64; x++) {
			Palette[x].r =0;
			Palette[x].g =x;
			Palette[x].b =0;

			Palette[x+64].r = 0;
			Palette[x+64].b = x+64;
			Palette[x+64].b = 0;

			Palette[x+128].r = 0;
	 		Palette[x+128].g = x+64+64;
			Palette[x+128].b = 0;

			Palette[x+128+64].r = 0;
			Palette[x+128+64].g = x+64+64+64;
			Palette[x+128+64].b = 0;
		}		
	}
	if (palmod == 3) {
		for (x = 0; x<64; x++) {
			Palette[x].r = 3*x;
			Palette[x].g = 0;
			Palette[x].b =0;

			Palette[x+64].r = x*3;
			Palette[x+64].b = x*3;
			Palette[x+64].b = 0;

			Palette[x+128].r = 255 - x*3;
	 		Palette[x+128].g = 0;
			Palette[x+128].b = 0;

			Palette[x+128+64].r = 255 - x*3;
			Palette[x+128+64].g = 255 - x*3;
			Palette[x+128+64].b =0;
		}	
	}	
	SDL_SetColors(dst, Palette, 0, 255);
}	
void usage() {
	printf("Usage plasma {-h -f {-r 320x200, 640x480, 800x600} }\n");
	exit(1);
}	
int main (int argc, char *argv[]) {
	SDL_Surface *screen;
	unsigned char vptr1, vptr2, hptr1, hptr2; // Horisontale og vertikale pointere
	int x,y,i, xw, yw, factor, fullscreen, pal;
	Uint8 *keys;
	Uint8 state;
	unsigned char table[256];  // Sinustabellen
	unsigned char ptr[4]; // For å holde styr på utgangsposisjonene
	SDL_Event event;
	xw = 320; yw = 200;
	fullscreen = 0;
	factor = 1;
	pal = 1;
	for (i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-h") == 0) 
			usage();
		if(strcmp(argv[i], "-f") == 0) {
			fullscreen = 1;
		}
		if(strcmp(argv[i],"-r") == 0) {  
		 	xw = 0; yw = 0;
			if (argc == i+1) 
				usage();
		 	
			if (strcmp(argv[i+1],"320x200") == 0) {
				xw = 320; yw = 200;
			}
			
			if (strcmp(argv[i+1],"640x480") == 0) {
				xw = 640; yw = 480;
				factor = 4;
			}

			if (strcmp(argv[i+1],"800x600") == 0) {
				xw = 800; yw = 600;
				factor = 8;
			}
		}	
	}	
	if (xw == 0) 
		usage();	
	// Iinitierer SDL video, bailer om den ikke får til
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Couldn't initiate video - aborting now!\n");
		return(1);
	}
	// Default exit handler
	atexit(SDL_Quit);
	
	// Jeg vil gjerne mottat eventer
	SDL_SetEventFilter(FilterEvents);
	
	// Setter opp vinduet 400x360 8 bits farger
	if (fullscreen)
		screen = SDL_SetVideoMode(xw, yw, 8, SDL_SWSURFACE|SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(xw, yw, 8, SDL_SWSURFACE);
	SDL_ShowCursor(0);	
	// Initierer farge paletten
	initpalette(screen, pal);
	
	// Setter opp sinus tabell går fra 32-64-0-32
	for (i = 0; i < 256; i++)
		table[i] = (sin((double)i*360.0/255.0*M_PI/180.0)*32)+32;
	
	// Nullstiller bare
	for (i = 0; i<4; i++)
		ptr[i] = 0;
	hptr1 = hptr2 = vptr1 = vptr2 = 0;
	
	// Gå inn i loop hvor vi sjekker om bruker lukker vindu eller trykker escape
	while ( 1 == 1) {
		char *p = screen->pixels;
		SDL_PollEvent(&event);
		
		// Noen har trykket en tast
		if (event.type == SDL_KEYDOWN) {
			
			// Er det escape tro?
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				printf("Coded by: Audun Hove\n");
				return(1);
			}
		}
		keys = SDL_GetKeyState(NULL);
		if (keys[SDLK_SPACE]) {
			pal = ((pal +1) % numcols) + 1;
			initpalette(screen, pal);	
			SDL_Delay(500);
		}	
		// Selve plasma delen begynner her
		
		// Setter de to vertikale pointerne sin utgangsverdi
		vptr1 = ptr[2];
		vptr2 = ptr[3];
		
		// Går fra topp til bunn
		for (y = 0; y < screen->h; y++) {
			// Beveger oss rundt i sinustabellen 
			// (kan se rart ut, vil vi ikke gå utenfor arrayet etterhvert?
			// Nei, fordi dette er unsigned char som er 8 bits, derfor blir 
			// den wrappet rundt til 0 igjen når den når 255
			vptr1++; 
			vptr2+=2; 

			// Setter de to horisontale pointerne tilbake til utgangsverdi
			hptr1 = ptr[0];
			hptr2 = ptr[1]; 
			
			// Går fra venstre til høyre	
			for (x = 0; x < screen->w;  x++) {

				// Samme som for vertikal bevegelse som nevnt over
				hptr1 += 2;
				hptr2 += 3;

				// Selve cluet med plasma effekt - vi henter fargeverdi
				// fra sinustabellen.
				*(p++) = table[hptr1] + table[hptr2] + table[vptr1] + table[vptr2];
			}
		} // Vi har nå vært igjennom en full frame

		// Endrer litt på utgangsverdien til vertikale og horisontale pointere
		// for å få plasmaen til å bevege seg
		ptr[0] -= 1 * factor;
		ptr[1] += 1 * factor;
		ptr[2] -= 1 * factor;
		ptr[3] += 1 * factor;

		// Oppdaterer skjermen
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}		
	return (1);
}
				
	
