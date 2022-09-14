#include "LowRenderer/ShaderProgram.hpp"
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>
#include <iostream>

using namespace Resources;

ShaderProgram::ShaderProgram(Shader* _vertexShader, Shader* _fragmentShader) 
{
	type = Resource::ResourceType::R_SHADERPROGRAM;	
	vertexShader = _vertexShader;
	fragmentShader = _fragmentShader;
}

void ShaderProgram::Bind()
{
	int success;
	char infoLog[255];

	program = glCreateProgram();
	glAttachShader(program, vertexShader->shaderKey);
	glAttachShader(program, fragmentShader->shaderKey);
	glLinkProgram(program);
	// check for linking errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		//std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl << "End infoLog" << std::endl;
	}
	glDeleteShader(vertexShader->shaderKey);
	glDeleteShader(fragmentShader->shaderKey);
	isLoaded = true;
}

int ShaderProgram::GetProgram() {
	return program;
}

void ShaderProgram::Unload() {
	glDeleteProgram(program);
}


