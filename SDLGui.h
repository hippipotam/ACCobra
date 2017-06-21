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
#include <chrono>
#include "GLSLShader.h"


const int SCREEN_FULLSCREEN = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int NUM_X = 12;
const int NUM_Z = 12;
const int SIZE_X = NUM_X;
const int SIZE_Z = NUM_Z;
const int HALF_SIZE_X = SIZE_X / 2;
const int HALF_SIZE_Z = SIZE_Z / 2;
const int TOTAL_INDICES = SIZE_X * SIZE_Z;

const float SPEED = 10.f;

class SDLGui {
	SDL_Window *m_window;
	SDL_GLContext m_maincontext;
	GLSLShader m_shader;

	GLint m_vpWidth, m_vpHeight; // viewport width and height

	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	Vertex vertices[NUM_X*NUM_Z];
	GLushort indices[NUM_X*NUM_Z];

	GLuint m_vaoID;
	GLuint m_vboVerticesID;
	GLuint m_vboIndicesID;

	glm::mat4 P;
	glm::mat4 MV;

	float m_aspect;
	bool m_state;
	int oldX, oldY;
	float dist = 1.f;
	float rX = 0.f, rY = 0.f;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point elapsed;

private:
	void OnResize(int w, int h, bool perspective);
	/* \brief Load shaders
	 * 	\param vshader		path to vertex shader
	 * 	\param fhsader		path to fragment shader
	 * 	\param attributes	attributes
	 * 	\param uniforms		uniforms
	 */
	void LoadShaders(const std::string& vshader, const std::string& fshader, std::vector<std::string> attributes, std::vector<std::string> uniforms);

	/** Create geometry and topology */
	void CreateSimpleColoredTriangle();
	void CreateRippleMesh();
	void CreateGeometryAndTopology();

	// Store the geometry and topology in the buffer objects
	void StoreGeometryAndTopology(std::vector<std::string> attributes, GLsizei stride = 0);

public:
	SDLGui();
	virtual ~SDLGui();

	bool Init(const char *caption);

	void SoftwareVersions();

	void OnShutdown();
	void Resize(bool perspective);

	void OnInit();
	void OnInitRippleMesh();

	void OnRender();
	void OnRenderRippleMesh();

	void OnMouseDown(SDL_MouseButtonEvent button, bool up, int x, int y);
	void OnMouseMove(int x, int y);

	void SwapWindow();


};

#endif /* SDLGUI_H_ */
