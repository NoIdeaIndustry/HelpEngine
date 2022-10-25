#include <string>

#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>

#include "Utils/Input.hpp"

using namespace std;
using namespace Core::myMath;

 GLFWwindow* Input::window;
 Core::myMath::Vec2 Input::mousePosition;
 Core::myMath::Vec2 Input::mouseDelta;

void Input::Init(GLFWwindow* _window) {
	window = _window;
	for (size_t i = 0; i < 348; i++) {
		keyMap[i] = 0;
	}
}

float Input::GetHorizontalAxis() {
	if (glfwGetKey(window, newKeyRight) == GLFW_PRESS)
		return 1;
	if (glfwGetKey(window, newKeyLeft) == GLFW_PRESS)
		return -1;

	return 0;
}

float Input::GetVerticalAxis() {
	if (glfwGetKey(window, newKeyForward) == GLFW_PRESS)
		return 1;
	if (glfwGetKey(window, newKeyBackward) == GLFW_PRESS)
		return -1;

	return 0;
}

Vec2 Input::GetMouseDelta() {
	return mouseDelta;
}

void Input::Update() {
	double mousePosX, mousePosY;
	glfwGetCursorPos(window, &mousePosX, &mousePosY);
	mouseDelta.x = mousePosX - mousePosition.x;
	mouseDelta.y = mousePosY - mousePosition.y;

	mousePosition.x = mousePosX;
	mousePosition.y = mousePosY;



	//DisplayGUI();
	anyKeyDown = false;
	for (size_t i = 0; i < 348; i++) {
		if (glfwGetKey(window, i) == GLFW_PRESS) {
			if (keyMap[i] == 0) { keyMap[i] = 2; anyKeyDown = true; lastKeyPressed = i; }
			else keyMap[i] = 1;
		}
		if (glfwGetKey(window, i) == GLFW_RELEASE) {
			keyMap[i] = 0;
		}
	}
}

bool Input::IsKeyPressed(int key) {
	return keyMap[key] > 0;
}

bool Input::IsKeyDown(int key) {
	return keyMap[key] == 2;
}

bool Input::IsAnyKeyDown() {
	return anyKeyDown;
}

int Input::GetLastKeyPressed() {
	return lastKeyPressed;
}

bool Input::IsMouseButtonPressed(int mouseButton) {
	return glfwGetMouseButton(window, mouseButton);
}


void Input::DisplayGUI() {
	ImGui::Begin("Input");

	ImGui::Text(("Vertical axis : " + std::to_string((int)GetVerticalAxis())).c_str());
	ImGui::Text(("Horizontal axis : " + std::to_string((int)GetHorizontalAxis())).c_str());
	ImGui::Text(("Mouse delta : (" + std::to_string((int)GetMouseDelta().x) + " ; " + std::to_string((int)GetMouseDelta().y) + ")").c_str());

	for (int i = 0; i < 348; i++) {
		ImGui::Text(("key " + to_string(i) + " : " + to_string(keyMap[i])).c_str());
	}

	ImGui::End();
}
