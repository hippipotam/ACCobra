/*
 * main.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <cstdio>

#include "SDLGui.h"
#include "log.h"


bool gRenderQuad = false;

//template <typename valType>
//GLM_FUNC_QUALIFIER detail::tmat4x4<valType> ortho
//(
//    valType const & left,
//    valType const & right,
//    valType const & bottom,
//    valType const & top,
//    valType const & zNear,
//    valType const & zFar
//)
//{
//    detail::tmat4x4<valType> Result(1);
//    Result[0][0] = valType(2) / (right - left);
//    Result[1][1] = valType(2) / (top - bottom);
//    Result[2][2] = - valType(2) / (zFar - zNear);
//    Result[3][0] = - (right + left) / (right - left);
//    Result[3][1] = - (top + bottom) / (top - bottom);
//    Result[3][2] = - (zFar + zNear) / (zFar - zNear);
//    return Result;
//}


int main(int argc, char *argv[])
{
	SDLGui SDLGuiWrapper;
	SDL_Event ev;
	bool quit = false;
	int w,h;

	if (!SDLGuiWrapper.Init("OpenGL 4.5")) {
		// TODO exit
		ERROR_LOG() << "Can't initialize openGL";
		exit(1);
	}

	SDLGuiWrapper.OnInitRippleMesh();
	printf("WSize [ %d; %d ]\n", w, h);
	SDLGuiWrapper.Resize(true);


	while (!quit) {

		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT) {// || ev.key.keysym.sym == SDLK_q) {
				quit = true;
				printf("Quit\n"); // TODO QUIT!???
			} else if (ev.key.keysym.sym == SDLK_f) {
				gRenderQuad = true;
				printf("render quad!\n");
			} else if (ev.type == SDL_MOUSEBUTTONDOWN) {
//				DEBUG_LOG() << "Mouse button DOWN! pos [" << ev.button.x << ":" << ev.button.y << "]" << std::endl;
				SDLGuiWrapper.OnMouseDown(ev.button, false, ev.button.x, ev.button.y);
			} else if (ev.type == SDL_MOUSEBUTTONUP) {
//				DEBUG_LOG() << "Mouse button UP! pos [" << ev.button.x << ":" << ev.button.y << "]" << std::endl;
				SDLGuiWrapper.OnMouseDown(ev.button, true, ev.button.x, ev.button.y);
			} else if (ev.type == SDL_MOUSEMOTION) {
				SDLGuiWrapper.OnMouseMove(ev.button.x, ev.button.y);
			}
		}
		SDLGuiWrapper.OnRenderRippleMesh();

		SDLGuiWrapper.SwapWindow();
		usleep(10000);
	}

	// TODO


	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDLGuiWrapper.OnShutdown();
//	SDL_GL_DeleteContext(m_maincontext);
//	SDL_DestroyWindow(m_window);
//	SDL_Quit();
	printf("Done\n");
	return 0;
}

