#include "Components/CameraBehaviour.hpp"
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "Utils/Time.hpp"
#include "Utils/Input.hpp"

void CameraBehaviour::Start() {

}

void CameraBehaviour::Update() {
	if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
		gameObject->transform.rotation.x += Input::GetMouseDelta().y * 0.2f;
	}
}

void CameraBehaviour::DisplayGUI() {
	if (ImGui::CollapsingHeader("Camera Behaviour")) {

	}
}

void CameraBehaviour::Destroy() {

}