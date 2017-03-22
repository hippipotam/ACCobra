/*
 * GLSLShader.cpp
 *
 *  Created on: Mar 22, 2017
 *      Author: rik
 */

#include "GLSLShader.h"

GLSLShader::GLSLShader() {
	// TODO Auto-generated constructor stub

}

GLSLShader::~GLSLShader() {
	// TODO Auto-generated destructor stub
}

void GLSLShader::LoadFromString(GLenum whichShader, const std::string &source)
{
	//TODO LoadFromString
}

void GLSLShader::LoadFromFile(GLenum whichShader, const std::string &filename)
{
	//TODO LoadFromFile
}

void GLSLShader::CreateAndLinkProgram()
{
	//TODO CreateAndLinkProgram
	// glCreateProgram
	// glAttachShader
	// glLinkProgram
	// glGetProgram
}

void GLSLShader::Use()
{
	//TODO Use
}

void GLSLShader::UnUse()
{
	//TODO UnUse
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
