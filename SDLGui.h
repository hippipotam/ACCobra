/*
 * SDLGui.h
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#ifndef SDLGUI_H_
#define SDLGUI_H_


#include <SDL2/SDL.h>

class SDLGui {
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;

public:
	SDLGui();
	virtual ~SDLGui();

	bool Init();


};

#endif /* SDLGUI_H_ */
