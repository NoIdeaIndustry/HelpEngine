#include "LowRenderer/Light.hpp"
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>
#include "LowRenderer/Renderer.hpp"

#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>

using namespace LowRenderer;
using namespace Core::myMath;
using namespace Core::DataStructure;

Vec4 Light::ambientColor;

Light::Light(int _type) {
	type = (LightType)_type;

	MonoBehaviour();
	ambientColor = Vec4(1.f, 1.f, 1.f, 0.1f);
	color = Vec3(1.f, 1.0f, 1.0f);

	constantAttenuation = 1;
	linearAttenuation = 0.5f;
	quadraticAttenuation = 0.6f;

	spotCutoff = 45;

	intensity = 1;
}

void Light::Start() {
	Renderer::lights.push_back(this);
}

void Light::Render(int i) {
	Vec3 lightGlobalPos = gameObject->transform.GetGlobalPosition();
	std::string prefix = "lights[" + std::to_string(i) + "].";

	glUniform1i(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "type").c_str()), (int)type);

	Vec4 direction = gameObject->transform.GetModel() * Vec4(0, -1, 0, 0);

	switch (type) {
		case (LightType::L_DIRECTIONAL):
			glUniform3fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "direction").c_str()), 1, &direction.x);
			break;
	
		case (LightType::L_POINT):
			glUniform3fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "position").c_str()), 1, &lightGlobalPos.x);
			glUniform1f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "constantAttenuation").c_str()), constantAttenuation);
			glUniform1f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "linearAttenuation").c_str()), linearAttenuation);
			glUniform1f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "quadraticAttenuation").c_str()), quadraticAttenuation);
			break;

		case (LightType::L_SPOT):
			glUniform3fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "position").c_str()), 1, &lightGlobalPos.x);
			glUniform3fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "direction").c_str()), 1, &direction.x);
			glUniform1f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "spotCutoff").c_str()), cosf(spotCutoff * (mPI / 180)));
	}

	glUniform3fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "color").c_str()), 1, &color.x);
	glUniform1f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), (prefix + "intensity").c_str()), intensity);

	glUniform4fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "ambientColor"), 1, &ambientColor.x);
}

void Light::DisplayGUI() {
	if (ImGui::CollapsingHeader("Light")) {
		ImGui::ColorEdit4("Ambient Color", &ambientColor.x);
		ImGui::ColorEdit3("Diffuse Color", &color.x);
		ImGui::DragFloat("Intensity", &intensity, 0.01f, 0, 3);

		const char* lightType = "Directional\0Point\0Spot";
		int t = (int)type;
		ImGui::Combo("Light Type", &t, lightType);
		type = (LightType)t;

		switch (type) {
			case (LightType::L_DIRECTIONAL):
				break;

			case (LightType::L_POINT):
				ImGui::DragFloat("Constant Attenuation", &constantAttenuation, 0.01f, 0, 2);
				ImGui::DragFloat("Linear Attenuation", &linearAttenuation, 0.01f, 0, 5);
				ImGui::DragFloat("Quadratic Attenuation", &quadraticAttenuation, 0.01f, 0, 5);
				break;

			case (LightType::L_SPOT):
				ImGui::DragFloat("Spot Cutoff", &spotCutoff, 0.05f, 0, 180);
				break;
		}
	}
}

void Light::Update() {
}

void Light::Destroy() {
	Renderer::lights.erase(std::remove(Renderer::lights.begin(), Renderer::lights.end(), this), Renderer::lights.end());
}