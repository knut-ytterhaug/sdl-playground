#include <SDL/SDL.h>

SDL_Color HSVtoRGB(int h, int s, int v)
{
	int ra, rb;
	int r, g, b;
	SDL_Color RGB;
	
	ra = h / 60;
	rb = h % 60;

	switch(ra)
	{
		case 0:
			r = 255;
			g = rb*255.0/60.0;
			b = 0;
			break;
		case 1:
			r = 255-rb*255.0/60.0;
			g = 255;
			b = 0;
			break;
		case 2:
			r = 0;
			g = 255;
			b = rb*255.0/60.0;
			break;
		case 3:
			r = 0;
			g = 255-rb*255.0/60.0;
			b = 255;
			break;
		case 4:
			r = rb*255.0/60.0;
			g = 0;
			b = 255;
			break;
		case 5:
			r = 255;
			g = 0;
			b = 255-rb*255.0/60.0;
			break;
	}

	if(s != 100)
	{
		r = r + ((255.0-r)/100.0*(100.0-s));
		g = g + ((255.0-g)/100.0*(100.0-s));
		b = b + ((255.0-b)/100.0*(100.0-s));
	}
	
	if(v != 100)
	{
		r = r * v / 100.0;
		g = g * v / 100.0;
		b = b * v / 100.0;
	}
	
	RGB.r = r;
	RGB.g = g;
	RGB.b = b;
	
	return RGB;
}

