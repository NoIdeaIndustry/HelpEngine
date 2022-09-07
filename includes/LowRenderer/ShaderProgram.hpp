#pragma once
#include "Shader.hpp"
#include <string>
#include "Math.hpp"
#include "Resources/Resource.hpp"

namespace Resources
{
	class ShaderProgram : public Resource
	{
	public :
		ShaderProgram(int vertexShader, int fragmentShader);
		void Unload();
		~ShaderProgram();
		int GetProgram();

	private :
		int program;
	};
}