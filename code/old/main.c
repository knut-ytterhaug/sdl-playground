#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

static GLboolean should_rotate = GL_TRUE;

static void quit_tutorial(int code)
{
	SDL_Quit();
	exit(code);
}

static void handle_key_down(SDL_keysym* keysym)
{
	switch(keysym->sym)
	{
		case SDLK_ESCAPE:
			quit_tutorial(0);
			break;
		case SDLK_SPACE:
			should_rotate = !should_rotate;
			break;
		default:
			break;
	}
}

static void process_events(void)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				handle_key_down(&event.key.keysym);
				break;
			case SDL_QUIT:
				quit_tutorial(0);
				break;
		}
	}
}

static void draw_screen(void)
{
	static float angle = 0.0f;

	
	static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
	static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
	static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
	static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
	static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
	static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
	static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
	static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
	static GLubyte red[]    = { 255,   0,   0, 255 };
	static GLubyte green[]  = {   0, 255,   0, 255 };
	static GLubyte blue[]   = {   0,   0, 255, 255 };
	static GLubyte white[]  = { 255, 255, 255, 255 };
	static GLubyte yellow[] = {   0, 255, 255, 255 };
	static GLubyte black[]  = {   0,   0,   0, 255 };
	static GLubyte orange[] = { 255, 255,   0, 255 };
	static GLubyte purple[] = { 255,   0, 255,   0 };

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(angle, 0.0, 1.0, 0.0);

	if(should_rotate)
	{
		if(++angle > 360.0f)
		{
			angle = 0.0f;
		}
	}

	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( blue );
	glVertex3fv( v2 );

	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( blue );
	glVertex3fv( v2 );
	glColor4ubv( white );
	glVertex3fv( v3 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( black );
	glVertex3fv( v5 );
	glColor4ubv( orange );
	glVertex3fv( v6 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( orange );
	glVertex3fv( v6 );
	glColor4ubv( blue );
	glVertex3fv( v2 );

	glColor4ubv( black );
	glVertex3fv( v5 );
	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( purple );
	glVertex3fv( v7 );

	glColor4ubv( black );
	glVertex3fv( v5 );
	glColor4ubv( purple );
	glVertex3fv( v7 );
	glColor4ubv( orange );
	glVertex3fv( v6 );

	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( white );
	glVertex3fv( v3 );

	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( white );
	glVertex3fv( v3 );
	glColor4ubv( purple );
	glVertex3fv( v7 );

	glColor4ubv( white );
	glVertex3fv( v3 );
	glColor4ubv( blue );
	glVertex3fv( v2 );
	glColor4ubv( orange );
	glVertex3fv( v6 );

	glColor4ubv( white );
	glVertex3fv( v3 );
	glColor4ubv( orange );
	glVertex3fv( v6 );
	glColor4ubv( purple );
	glVertex3fv( v7 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( red );
	glVertex3fv( v0 );
	glColor4ubv( yellow );
	glVertex3fv( v4 );

	glColor4ubv( green );
	glVertex3fv( v1 );
	glColor4ubv( yellow );
	glVertex3fv( v4 );
	glColor4ubv( black );
	glVertex3fv( v5 );

	glEnd();

	SDL_GL_SwapBuffers();
}

static void setup_opengl(int width, int height)
{
	float ratio = (float)width/(float)height;

	glShadeModel(GL_SMOOTH);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glClearColor(0,0,0,0);

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, ratio, 1.0, 1024.0);
}

int main(int argc, char *argv[])
{
	const SDL_VideoInfo* info = NULL;
	int width = 0;
	int height = 0;
	int bpp = 0;
	int flags = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		quit_tutorial(1);
	}

	info = SDL_GetVideoInfo();

	if(!info)
	{
		fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
		quit_tutorial(1);
	}

	width = 640;
	height = 480;
	bpp = info->vfmt->BitsPerPixel;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	flags = SDL_OPENGL;

	if(SDL_SetVideoMode(width, height, bpp, flags) == 0)
	{
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quit_tutorial(1);
	}

	setup_opengl(width, height);

	while(1)
	{
		process_events();
		draw_screen();
	}

	return 0;
}
