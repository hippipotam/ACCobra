/*
 * SDLGui.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: rik
 */

#include "SDLGui.h"
#include "log.h"

//using namespace std;

SDLGui::SDLGui() :
	m_window(nullptr),
	m_maincontext(nullptr)
{
}

SDLGui::~SDLGui() {
	SDL_GL_DeleteContext(m_maincontext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool SDLGui::Init(const char *caption)
{
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		ERRO_LOG() << "Couldn't initialize SDL.";
		return false;
	}
	//		sdl_die("Couldn't initialize SDL.");
	atexit(SDL_Quit);

	// Default OpenGL is fine.
	SDL_GL_LoadLibrary(NULL);

	// Request an OpenGL 4.5 context (should be core)
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	// Also request a depth buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create the window
	m_window = SDL_CreateWindow(caption,
								SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL
								);
	if (m_window == nullptr) {
		ERRO_LOG() << "Couldn't create window";
		return false;
	}
//		sdl_die("Couldn't set video mode");

	m_maincontext = SDL_GL_CreateContext(m_window);
	if (m_maincontext == nullptr) {
		ERRO_LOG() << "Failed to create OpenGL context";
		return false;
	}
//		sdl_die("Failed to create OpenGL context");

	// Load OpenGL functions glad SDL
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	// Use v-sync
	SDL_GL_SetSwapInterval(1);

	// Disable depth test and face culling.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);



	// Set OpenGL viewport
	SDL_GL_GetDrawableSize(m_window, &m_vpWidth, &m_vpHeight);
	glViewport(0, 0, m_vpWidth, m_vpHeight);
	printf("Drawable size: w %d, h %d\n", m_vpWidth, m_vpHeight);

	return success;
}

void SDLGui::SoftwareVersions()
{
	// Check OpenGL properties
	printf("OpenGL loaded.\n");
	printf("Vendor:   %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version:  %s\n", glGetString(GL_VERSION));
	printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void SDLGui::OnShutdown()
{
	m_shader.DeleteShaderProgram();
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);
}

void SDLGui::OnResize(int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	g_aspect = float(h) / float(w);
	P = glm::ortho(-1,1,-1,1);
}

void SDLGui::Resize()
{
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	OnResize(w, h);

}

void SDLGui::SwapWindow()
{
	SDL_GL_SwapWindow(m_window);
}

void SDLGui::OnInit()
{
	m_shader.LoadFromFile(GL_VERTEX_SHADER, "shaders/shader1.vert");
	m_shader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/shader1.frag");
	m_shader.CreateAndLinkProgram();
	m_shader.Use();
		m_shader.AddAttribute("vVertex");
		m_shader.AddAttribute("vColor");
		m_shader.AddUniform("MVP");
	m_shader.UnUse();

	std::cout << "Attribute: " << m_shader["vVertex"] << "," << m_shader["vColor"] << std::endl;

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

	printf("shader[\"vVertex\"]=%d\n", m_shader["vVertex"]);
	printf("shader[\"vColor\"]= %d\n", m_shader["vColor"]);
	printf("size(Vertex.position)=%ld\n", sizeof(vertices[0].position));
	printf("size(GLfloat)");
	printf("size(vertices[0].position.x)=%ld\n", sizeof(vertices[0].position.x));
//	printf("v0p= %d\n", vertices[0].position.length());

	glEnableVertexAttribArray(m_shader["vVertex"]);
	glVertexAttribPointer(m_shader["vVertex"], 3, GL_FLOAT, GL_FALSE, stride, 0);

	glEnableVertexAttribArray(m_shader["vColor"]);
	glVertexAttribPointer(m_shader["vColor"], 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

}

void SDLGui::OnRender()
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
	m_shader.Use();
		glUniformMatrix4fv(m_shader("MVP"), 1, GL_FALSE, glm::value_ptr(P*MV));
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
	m_shader.UnUse();

//	SDL_GetWindowSize(g_window, &w, &h);
//	glViewport(0, 0, w, h);
//	glClearColor(0.0f, 0.2f, 0.4f, 0.0f);
}
