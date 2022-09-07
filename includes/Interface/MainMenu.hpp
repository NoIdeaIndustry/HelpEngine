#pragma once
#include "Core/Scene.hpp"
#include "Utils/Input.hpp"
#include "Resources/ResourceManager.hpp"
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <GLFW/includes/glfw3.h>


class MainMenu
{
public:
	Core::DataStructure::Scene scene;
	static GLFWwindow* window;

	bool isPressedPlay = false;
	bool isPressedOptions = false;
	bool isWaitingToSelect = false;
	bool isNewKeyForward = false;
	bool isNewKeyLeft = false;
	bool isNewKeyRight = false;
	bool isNewKeyBackward = false;
	bool isNewKeyJump = false;
	bool firstTime = true;

	

	void Update();
	void DisplayGUI(GLFWwindow* _window);
	void DisplayGUIOptions();
	void ReturnMainMenu(GLFWwindow* _window);
	void TextCentered(std::string text);
};