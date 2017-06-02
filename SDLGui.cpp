/*
 * SDLGui.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#include <iostream>
#include "SDLGui.h"

using namespace std;

SDLGui::SDLGui() :
	m_window(nullptr),
	m_renderer(nullptr)
{
	// TODO Auto-generated constructor stub

}

SDLGui::~SDLGui() {
	// TODO Auto-generated destructor stub
}

bool SDLGui::Init()
{
	bool success = true;

//	cout << "Initialize SDL for VIDEO...";
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		cout << "[ FALSE ]\nError: " << SDL_GetError() << endl;
//		success = false;
//	} else {
//		cout << "[ OK ]" << endl;
//		cout << "Create window...";
//		// https://wiki.libsdl.org/SDL_WindowFlags
//		m_window = SDL_CreateWindow("ACCobra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_SHOWN); //| SDL_WINDOW_BORDERLESS); //SDL_WINDOW_SHOWN); SDL_WINDOW_OPENGL
//		if (m_window == NULL) {
//			cout << "[ FALSE ]\nError: " << SDL_GetError() << endl;
//			success = false;
//		} else {
//			cout << "[ OK ]" << endl;
//			cout << "Create renderer for window...";
//			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
//			if (m_renderer == NULL) {
//				cout << "[ FALSE ]\nError: " << SDL_GetError() << endl;
//				SDL_DestroyWindow(m_window);
//				return false;
//			} else cout << "[ OK ]" << endl;
//		}
//	}
//
//
//
//	cout << "Create renderer for window...";
//	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
//	if (m_renderer == NULL) {
//		cout << "[ FALSE ]\nError: " << SDL_GetError() << endl;
//		SDL_DestroyWindow(m_window);
//		return false;
//	} else cout << "[ OK ]" << endl;
//
//	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0x00);
	return success;
}
