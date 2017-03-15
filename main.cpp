/*
 * main.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#include <cstdlib>
#include <cstdlib>

//#include "SDLGui.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>

const int SCREEN_FULLSCREEN = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


static SDL_Window *g_window = nullptr;
static SDL_GLContext g_maincontext;


static void sdl_die(const char *message) {
	fprintf(stderr, "%s: %s\n", message, SDL_GetError());
	exit(2);
}

void init_screen(const char *caption) {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		sdl_die("Couldn't initialize SDL.");
	atexit(SDL_Quit);
	SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create the window
	g_window = SDL_CreateWindow(
			caption,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL
			);
	if (g_window == nullptr) sdl_die("Couldn't set video mode");

	g_maincontext = SDL_GL_CreateContext(g_window);
	if (g_maincontext == nullptr)
		sdl_die("Failed to create OpenGL context");

	// Check OpenGL properties
	printf("OpenGL loaded\n");
	//....

	// Use v-sync
	SDL_GL_SetSwapInterval(1);

	// Disable depth test and face culling.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

}

int main(int argc, char *argv[])
{
//	SDLGui sdl;
	SDL_Event ev;
	bool quit = false;

	init_screen("OpenGL 4.5");

	while (!quit) {
		SDL_GL_SwapWindow(g_window);
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || ev.type == SDLK_q)
				quit = true;
		}
//		int w,h;
//		  SDL_GetWindowSize(window, &w, &h);
//		  glViewport(0, 0, w, h);
//		  glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	}


	return 0;
}

