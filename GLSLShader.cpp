/*
 * GLSLShader.cpp
 *
 *  Created on: Mar 22, 2017
 *      Author: rik
 */

#include "GLSLShader.h"
//#include <cstdio>
#include <fstream>
#include <iostream>

using namespace std;

GLSLShader::GLSLShader() :
		m_totalShaders(0)
{
	// TODO Auto-generated constructor stub


}

GLSLShader::~GLSLShader() {
	// TODO Auto-generated destructor stub
}

void GLSLShader::LoadFromString(GLenum whichShader, const std::string &source)
{
	GLint success;
	GLchar infoLog[512];
	const char *srcs = source.c_str();
	// Build compile SHADER
	GLuint shader = glCreateShader(whichShader);
	glShaderSource(shader, 1, &srcs, NULL);
	glCompileShader(shader);

	// Check for compile errors VERTEX_SHADER
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		printf("Error: shader compilation error: %s\n", infoLog);
	} else {
		m_shaders[m_totalShaders++] = shader;
	}

//	glCreateShader
//	glShaderSource
//	glCompileShader
//	glGetShaderInfoLog

}

void GLSLShader::LoadFromFile(GLenum whichShader, const std::string &filename)
{
	//TODO LoadFromFile
	ifstream ifs;
	string sourceShader("");

	ifs.open(filename.c_str(), ifstream::in);
	// TODO check stream open
	while (!ifs.eof()) {
		string str;
		getline(ifs, str);
		if (str.empty()) continue;
		str += "\n";
		sourceShader.append(str);
	}
	ifs.close();
	cout << endl;
	cout << "SHADER SOURCE:" << endl;
	cout << sourceShader << endl;

	LoadFromString(whichShader, sourceShader);

}

void GLSLShader::CreateAndLinkProgram()
{
	GLint success;
	GLchar infoLog[512];

	m_program = glCreateProgram();

	for (int i = 0; i < m_totalShaders; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}
	glLinkProgram(m_program);

	// Check the linking errors
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(m_program, sizeof(infoLog), NULL, infoLog);
		printf("Error: linking error: %s\n", infoLog);
	}


	// glCreateProgram
	// glAttachShader
	// glLinkProgram
	// glGetProgramInfoLog
}

void GLSLShader::Use()
{
	//TODO Use
	glUseProgram(m_program);
}

void GLSLShader::UnUse()
{
	//TODO UnUse
	glUseProgram(m_program);
}

void GLSLShader::AddAttribute(const std::string &attribute)
{
	//TODO AddAttribute
}

void GLSLShader::AddUniform(const std::string &uniform)
{
	//TODO AddUniform
}

void GLSLShader::DeleteShaderProgram()
{
	//TODO DeleteShaderProgram
}
