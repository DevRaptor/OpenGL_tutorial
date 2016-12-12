#include "ShaderProgram.h"

#include <vector>

#include "utility/Log.h"


ShaderProgram::ShaderProgram(const std::string& vert_path, const std::string& frag_path)
{
	//load shaders


	/*
	//after link program
	GLint result = GL_FALSE;
	int info_length;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
	if (info_length > 0)
	{
		std::string error_message;
		error_message.reserve(info_length + 1);
		glGetProgramInfoLog(program, info_length, NULL, &error_message[0]);
		Logger::Log("Shader program error: ", std::string(&error_message[0]));
	}
	*/


	//clean
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::UseProgram()
{

}

GLuint ShaderProgram::GetProgram()
{

	return 0;
}