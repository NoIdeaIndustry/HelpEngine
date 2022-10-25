#pragma once

#include <string>

#include "Shader.hpp"
#include "Math.hpp"
#include "Resources/Resource.hpp"

namespace Resources
{
	class ShaderProgram : public Resource
	{
	public:
		ShaderProgram(Shader* vertexShader, Shader* fragmentShader);

		void Bind() override;
		void Unload();
		~ShaderProgram();
		int GetProgram();

	private:
		int program;

		Shader* fragmentShader, *vertexShader;
	};
}