#pragma once

#include <string>
#include <iostream>

namespace Resources
{
	class Resource
	{
	public:
		Resource() {}
		~Resource() {}

		std::string name;

		enum class ResourceType : int {
			R_TEXTURE,
			R_MATERIAL,
			R_SHADER,
			R_SHADERPROGRAM,
			R_MODEL
		};

		ResourceType type;

		bool isLoaded = false;

		virtual void Load(const std::string& filepath) {}
		virtual void Bind() {}
		virtual void DisplayGUI(int index) {}
		virtual void Unload() {}
	};
}
