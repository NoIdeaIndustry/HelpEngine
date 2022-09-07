#pragma once
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>

class Time
{
public :
	static inline float time = 0;
	static inline float deltaTime = 0;

	static inline void UpdateTime()
	{
		float newTime = glfwGetTime();
		deltaTime = newTime - time;
		time = newTime;
	}
};