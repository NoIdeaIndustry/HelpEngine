#pragma once
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>

#include "Math.hpp"

class Input
{
public :
	
	inline static int newKeyForward = GLFW_KEY_W;
	inline static int newKeyLeft = GLFW_KEY_A;
	inline static int newKeyRight = GLFW_KEY_D;
	inline static int newKeyBackward = GLFW_KEY_S;
	inline static int newKeyJump = GLFW_KEY_SPACE;

	static void Update();

	static void Init(GLFWwindow* _window);

	static float GetHorizontalAxis();
	static float GetVerticalAxis();

	static bool IsKeyPressed(int key);
	static bool IsKeyDown(int key);
	static bool IsAnyKeyDown();
	static int GetLastKeyPressed();

	static bool IsMouseButtonPressed(int mouseButton);

	static Core::myMath::Vec2 GetMouseDelta();

private :
	static GLFWwindow* window;
	static Core::myMath::Vec2 mousePosition;
	static Core::myMath::Vec2 mouseDelta;

	static inline int keyMap[348];
	static inline bool anyKeyDown;
	static inline int lastKeyPressed;

	static void DisplayGUI();
};

