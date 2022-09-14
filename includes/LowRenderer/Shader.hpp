#pragma once

#include "Resources/Resource.hpp"

namespace Resources
{
	class Shader : public Resource
	{
	public :

		void Load() override;
		void Bind() override;

		enum ShaderType
		{
			VERTEX,
			FRAGMENT
		};

		int shaderKey;
		ShaderType shaderType;
		Shader(ShaderType _type, const std::string _filepath = "");

	private :
		std::string shaderSource;

	};
}