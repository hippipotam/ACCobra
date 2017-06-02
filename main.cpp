/*
 * main.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#include <cstdlib>
#include <cstdlib>
#include <iostream>

//#include "SDLGui.h"
#include <SDL2/SDL.h>
//#include <GL/gl.h>
#include "GLSLShader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//using namespace std;

const int SCREEN_FULLSCREEN = 1;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


static SDL_Window *g_window = nullptr;
static SDL_GLContext g_maincontext;
GLSLShader shader;

bool gRenderQuad = false;

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
	printf("Drawable size: w %d, h %d\n", vpWidth, vpHeight);

	glViewport(0, 0, vpWidth, vpHeight);
}

void OnInit()
{
	shader.LoadFromFile(GL_VERTEX_SHADER, "shaders/shader1.vert");
	shader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/shader1.frag");
	shader.CreateAndLinkProgram();
	shader.Use();
		shader.AddAttribute("vVertex");
		shader.AddAttribute("vColor");
		shader.AddUniform("MVP");
	shader.UnUse();

	std::cout << "Attribute: " << shader["vVertex"] << "," << shader["vColor"] << std::endl;

	// Create geometry and topology
	vertices[0].color = glm::vec3(1,0,0);
	vertices[1].color = glm::vec3(0,1,1);
	vertices[2].color = glm::vec3(0,0,1);

	vertices[0].position = glm::vec3(1,-1,0);
	vertices[1].position = glm::vec3(0,1,0);
	vertices[2].position = glm::vec3(-1,-1,0);
//	vertices[0].position = glm::vec3(-1,-1,0);
//	vertices[1].position = glm::vec3(0,1,0);
//	vertices[2].position = glm::vec3(1,-1,0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	GLsizei stride = sizeof(Vertex);//glm::vec3);//Vertex);//

	printf("sizeof:\n\tstride=%ld, Vertex=%ld, vertices=%ld, glm::vec3=%ld\n", stride, sizeof(Vertex), sizeof(vertices), sizeof(glm::vec3));
	printf("Vertex: %p offset: pos %ld, col %ld\n", &vertices[0], offsetof(Vertex, position), offsetof(Vertex, color));
	printf("addr: %p, %p, %p\n", &vertices[0],&vertices[1],&vertices[2]);
	printf("sizeof(indices)=%ld\n", sizeof(indices));


	// Store the geometry and topology in the buffer objects
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

	printf("shader[\"vVertex\"]=%d\n", shader["vVertex"]);
	printf("shader[\"vColor\"]= %d\n", shader["vColor"]);
	printf("size(Vertex.position)=%ld\n", sizeof(vertices[0].position));
	printf("size(GLfloat)");
	printf("size(vertices[0].position.x)=%ld\n", sizeof(vertices[0].position.x));
//	printf("v0p= %d\n", vertices[0].position.length());

	glEnableVertexAttribArray(shader["vVertex"]);
	glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);

	glEnableVertexAttribArray(shader["vColor"]);
	glVertexAttribPointer(shader["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

}

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

void OnResize(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	g_aspect = float(h) / float(w);
	// Orthographic projection matrix
//	P = glm::ortho<GLfloat>( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );
	P = glm::ortho<GLfloat>(-1.f,1.f,-1.f,1.f);
//	P = glm::ortho(-1.f,1.f,-1.f,1.f);
}

void OnShutdown()
{
	shader.DeleteShaderProgram();
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);
}

void OnRender()
{
//	glm::mat4 model_matrix;
	// Setup
	glEnable(GL_CULL_FACE);

	glDisable(GL_DEPTH_TEST);

	// Clear color buffer
//	glClearColor(0.0f, 0.2f, 0.4f, 0.0f);

	// Identity modelview matrix
	MV = glm::mat4();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader.Use();
		glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	shader.UnUse();

//	SDL_GetWindowSize(g_window, &w, &h);
//	glViewport(0, 0, w, h);
//	glClearColor(0.0f, 0.2f, 0.4f, 0.0f);
}


int main(int argc, char *argv[])
{
//	SDLGui sdl;
	SDL_Event ev;
	bool quit = false;
	int w,h;

	InitScreen("OpenGL 4.5");
	SoftwareVersions();


	SDL_GetWindowSize(g_window, &w, &h);

	OpenGLSettings();

	OnResize(w, h);
//	P = glm::ortho(0.f,1.f,0.f,1.f,-1.f,1.f);

	OnInit();
	printf("WSize [ %d; %d ]\n", w, h);

	while (!quit) {

		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT || ev.key.keysym.sym == SDLK_q)
				quit = true;
			else if (ev.key.keysym.sym == SDLK_f) {
				gRenderQuad = true;
				printf("render quad!\n");
			}

		}
		OnRender();

		SDL_GL_SwapWindow(g_window);
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	OnShutdown();
	SDL_GL_DeleteContext(g_maincontext);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
	printf("Done\n");
	return 0;
}

