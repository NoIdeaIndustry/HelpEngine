#pragma once

#include "GLAD/includes/glad.h"
#include <GLFW/includes/glfw3.h>

namespace Core
{
	struct AppInitializer {
		unsigned int APP_WIDTH, APP_HEIGHT;
		unsigned int APP_MAJOR, APP_MINOR;
		const char* APP_NAME;
	};

	class App
	{
		static void processInput(GLFWwindow* window);

	public:
		inline static AppInitializer p_AppSettings;

		static GLFWwindow* window;
		
		void Init();
		void Update();
	};

}
