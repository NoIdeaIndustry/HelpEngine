   #include "LowRenderer/Camera.hpp"
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "Utils/Input.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Utils/Debug.hpp"
#include "Resources/ResourceManager.hpp"
#include "LowRenderer/ShaderProgram.hpp"
#include "Core/App.hpp"

using namespace std;
using namespace LowRenderer;
using namespace Core::myMath;
using namespace Core::DataStructure;

Camera::Camera() {
	MonoBehaviour();
}

void Camera::Start() {
	Renderer::mainCamera = this;
	
	Renderer::shaderProgram = ((Resources::ShaderProgram*)Resources::ResourceManager::Get("ShaderProgram"));
}

void Camera::Update() {
	ManageInput();
	Renderer::Update();
}

void Camera::Render() {
	UpdateViewProjection();
}

void Camera::UpdateViewProjection() {
	int width, height;
	glfwGetWindowSize(Core::App::window, &width, &height);
	Renderer::modelViewMatrix = mat4x4::Inverse(gameObject->transform.GetModel()) * mat4x4::Perspective(fov, 0.01f, 400, (float)height / (float)width);
	glUniform3fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "viewPos"), 1, &gameObject->transform.position.x);
}

void Camera::ManageInput() {
	/*float speed = 0.4f;
	
	if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		gameObject->transform.rotation.x += Input::GetMouseDelta().y * 0.2f;
	}*/
}

void Camera::DisplayGUI() {
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::DragFloat("fov", &fov, 0.2f, 5, 180);
	}
}
