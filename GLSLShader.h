/*
 * GLSLShader.h
 *
 *  Created on: Mar 22, 2017
 *      Author: rik
 */

#ifndef GLSLSHADER_H_
#define GLSLSHADER_H_

#include <string>
#include <map>
//#include <GL/gl.h>
#include <glad/glad.h>

class GLSLShader {
public:
	GLSLShader();
	~GLSLShader();

	void LoadFromString(GLenum whichShader, const std::string &source);
	void LoadFromFile(GLenum whichShader, const std::string &filename);
	void CreateAndLinkProgram();
	void Use();
	void UnUse();
	void AddAttribute(const std::string &attribute);
	void AddUniform(const std::string &uniform);
	void DeleteShaderProgram();

private:
	enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER };
	GLuint m_program;
	int m_totalShaders;
	GLuint m_shaders[3];
	std::map<std::string, GLuint> m_attributeList;
	std::map<std::string, GLuint> m_uniformLocationList;

};

#endif /* GLSLSHADER_H_ */
