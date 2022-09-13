#pragma once

#include <string>

#include "Resource.hpp"
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>

namespace Resources
{
	class Texture : public Resource
	{
	public :
		Texture();
		~Texture();

		void Load(const std::string& filepath) override;
		void Unload();
		void DisplayGUI(int index) override;

		static void InitSampler();
		static GLuint sampler;

		GLuint GetTexKey();
		int GetWidth();
		int GetHeight();

	private :
		GLuint texKey;
		int width, height;
	};
}
