#include "LowRenderer/Shader.hpp"
#include <fstream>
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>
#include "Utils/Debug.hpp"

using namespace Resources;
using namespace std;

Shader::Shader(ShaderType _type)
{
	type = Resource::ResourceType::R_SHADER;
	Resource();
	shaderType = _type;
}

void Shader::Load(const string& filepath)
{
	fstream file;
	file.open(filepath.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);


	if (file) {

		string shaderSource;
		string line;
		while (getline(file, line))
		{
			shaderSource += '\n' + line;
		}
		const char* buffer = shaderSource.c_str();
		file.close();

		switch (shaderType)
		{
		case(VERTEX): shaderKey = glCreateShader(GL_VERTEX_SHADER); break;
		case(FRAGMENT): shaderKey = glCreateShader(GL_FRAGMENT_SHADER); break;
		default: break;
		}

		glShaderSource(shaderKey, 1, &buffer, NULL);
		glCompileShader(shaderKey);

		int success;
		char infoLog[512];
		glGetShaderiv(shaderKey, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderKey, 512, NULL, infoLog);
			//std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	else
	{
		DEBUG_LOGERROR("Error opening file " + filepath);
	}
	file.close();
}




