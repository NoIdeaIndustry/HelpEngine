#pragma once

#include "Resources/Resource.hpp"

namespace Resources
{
	class Shader : public Resource
	{
	public:
		void Load(const std::string& filepath) override;
		enum ShaderType {
			VERTEX,
			FRAGMENT
		};

		int shaderKey;
		ShaderType shaderType;
		Shader(ShaderType _type);
	};
}