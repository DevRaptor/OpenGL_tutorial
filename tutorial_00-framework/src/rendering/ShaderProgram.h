#pragma once

#include <string>

#define GLEW_STATIC //needed to static link GLEW
#include <GL/glew.h>
#include <glm/glm.hpp>


class ShaderProgram
{
public:
	ShaderProgram(const std::string& vert_path, const std::string& frag_path);
	~ShaderProgram();

	void UseProgram();
	GLuint GetProgram();

private:
};

