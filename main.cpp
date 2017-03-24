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
//#include <GL/gl.h>
#include "GLSLShader.h"

const int SCREEN_FULLSCREEN = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


static SDL_Window *g_window = nullptr;
static SDL_GLContext g_maincontext;

bool gRenderQuad = false;


static void sdl_die(const char *message) {
	fprintf(stderr, "%s: %s\n", message, SDL_GetError());
	exit(2);
}

void InitScreen(const char *caption) {
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

	// Load OpenGL functions glad SDL
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	// Use v-sync
	SDL_GL_SetSwapInterval(1);

	// Disable depth test and face culling.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

}

void SoftwareVersions()
{
	// Check OpenGL properties
	printf("OpenGL loaded.\n");
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
	printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void OpenGLSettings()
{
	GLint vpWidth, vpHeight; // viewport width and height
	SDL_GL_GetDrawableSize(g_window, &vpWidth, &vpHeight);

	glViewport(0, 0, vpWidth, vpHeight);
}

void Render()
{
//	int w,h;
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	SDL_GetWindowSize(g_window, &w, &h);
//	glViewport(0, 0, w, h);
//	glClearColor(0.0f, 0.2f, 0.4f, 0.0f);

}

int main(int argc, char *argv[])
{
//	SDLGui sdl;
	SDL_Event ev;
	bool quit = false;

	InitScreen("OpenGL 4.5");
	SoftwareVersions();

	GLSLShader shader;
	shader.LoadFromFile(GL_VERTEX_SHADER, "shaders/shader.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/shader.frag");
	shader.CreateAndLinkProgram();

	while (!quit) {

		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || ev.key.keysym.sym == SDLK_q)
				quit = true;
			else if (ev.key.keysym.sym == SDLK_f) {
				gRenderQuad = true;
				printf("render quad!\n");
			}

		}
		Render();

		SDL_GL_SwapWindow(g_window);
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(g_maincontext);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
	printf("Done\n");
	return 0;
}

