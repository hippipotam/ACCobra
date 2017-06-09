/*
 * SDLGui.h
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#ifndef SDLGUI_H_
#define SDLGUI_H_

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "GLSLShader.h"

const int SCREEN_FULLSCREEN = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDLGui {
	SDL_Window *m_window;
	SDL_GLContext m_maincontext;
	GLSLShader m_shader;
//	SDL_Renderer *m_renderer;
//	SDL_Event event;

	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	Vertex vertices[3];
	GLushort indices[3];

	GLuint vaoID;
	GLuint vboVerticesID;
	GLuint vboIndicesID;

	glm::mat4 P;
	glm::mat4 MV;

	float g_aspect;

public:
	SDLGui();
	virtual ~SDLGui();

	bool Init(const char *caption);
	void SoftwareVersions();
	void OpenGLSettings();
	void OnShutdown();
	void Resize();

	void OnInit();
	void OnRender();

	void SwapWindow();


};

#endif /* SDLGUI_H_ */
