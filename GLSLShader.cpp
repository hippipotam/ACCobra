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
#include <cstdio>

#define LOG cout << "[ " << __FUNCTION__ << " ]: "

//#define INFO_LOG(...) fprintf(cerr, __VA_ARGS__);
//cout << "[ INFO ]-[ " << __FUNCTION__ << " ]: " << __VA_ARGS__ << endl
#define ERR_LOG(x) 	cerr << "[ ERRO+ ]-[ " << __FUNCTION__ << " ]: " << x << endl

using namespace std;

GLSLShader::GLSLShader() :
		m_program(0),
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

	for (int i = 0; i < m_totalShaders; i++)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);

	// Check the linking errors
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(m_program, sizeof(infoLog), NULL, infoLog);
		printf("Error: linking error: %s\n", infoLog);
	}

	for (int i = 0; i < m_totalShaders; i++)
		glDeleteShader(m_shaders[i]);
	m_totalShaders = 0;


	// glCreateProgram
	// glAttachShader
	// glLinkProgram
	// glGetProgramInfoLog
}

void GLSLShader::Use()
{
	 // Activate shading program
	glUseProgram(m_program);
}

void GLSLShader::UnUse()
{
	// Deactivate shading program
	glUseProgram(m_program);
}

void GLSLShader::AddAttribute(const std::string &attribute)
{
	GLint location = glGetAttribLocation(m_program, attribute.c_str());
	if (location < 0)
		cerr << "[ " << __FUNCTION__ << " ] cannot get attribute location \"" << attribute << "\""<< endl;
	else {
		cout << __FUNCTION__ << ": " << location << " (\"" << attribute << "\")" << endl;
		m_attributeList.emplace(attribute, location);
	}
}

void GLSLShader::AddUniform(const std::string &uniform)
{
	GLint location = glGetUniformLocation(m_program, uniform.c_str());
	if (location < 0)
		cerr << "[ " << __FUNCTION__ << " ] cannot get uniform location \"" << uniform << "\"" << endl;
	else {
		LOG << "Ha bla!" << endl;
//		ERR_LOG("Cannot find attribute \"" attribute);
		//cout << __FUNCTION__ << ": " << location << " (\"" << uniform << "\")" << endl;
		m_uniformLocationList.emplace(uniform, location);
	}
//	INFO_LOG("Hey ho!");
}

GLuint GLSLShader::operator[] (const std::string &attribute)
{
	GLuint res = -1;
	try {
		res = m_attributeList.at(attribute);
	} catch(...) {

		cerr << "[ " << __FUNCTION__ << " ] Cannot find attribute \"" << attribute << "\"" << endl;
		res = 0;
	}
	return res;
}

GLuint GLSLShader::operator() (const std::string &uniform)
{
	return m_uniformLocationList[uniform];
}

void GLSLShader::DeleteShaderProgram()
{
	//TODO DeleteShaderProgram
	for (int i = 0; i < m_totalShaders; i++)
		glDeleteShader(m_shaders[i]);
	m_totalShaders = 0;

	glDeleteProgram(m_program);
}


