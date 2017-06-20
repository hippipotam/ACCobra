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
#include <vector>
#include "GLSLShader.h"


const int SCREEN_FULLSCREEN = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int NUM_X = 3;
const int NUM_Z = 3;
const int SIZE_X = 3;
const int SIZE_Z = 3;
const int HALF_SIZE_X = SIZE_X / 2;
const int HALF_SIZE_Z = SIZE_Z / 2;

class SDLGui {
	SDL_Window *m_window;
	SDL_GLContext m_maincontext;
	GLSLShader m_shader;

	GLint m_vpWidth, m_vpHeight; // viewport width and height

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

private:
	void OnResize(int w, int h);
	/* Load shaders
	 * 	vshader		: path to vertex shader
	 * 	fhsader		: path to fragment shader
	 * 	attributes	: attributes
	 * 	uniforms	: uniforms
	 */
	void LoadShaders(const std::string& vshader, const std::string& fshader, std::vector<std::string> attributes, std::vector<std::string> uniforms);

	/* Create geometry and topology */
	void CreateSimpleColoredTriangle();
	void CreateRippleMesh();
	void CreateGeometryAndTopology();

public:
	SDLGui();
	virtual ~SDLGui();

	bool Init(const char *caption);

	void SoftwareVersions();

	void OnShutdown();
	void Resize();

	void OnInit();
	void OnInit2();

	void OnRender();

	void SwapWindow();


};

#endif /* SDLGUI_H_ */
