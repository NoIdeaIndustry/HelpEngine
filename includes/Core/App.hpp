#pragma once
#include "GLAD/includes/glad.h"
#include <GLFW/includes/glfw3.h>

namespace Core
{
	

	struct AppInitializer
	{
		int width, height;
		int major, minor;
		char* name;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};

	class App
	{
		static void processInput(GLFWwindow* window);

	public :
		static GLFWwindow* window;
		inline static int height, width;
		
		void Init(AppInitializer initializer);
		void Update();
		
	};
	

}
