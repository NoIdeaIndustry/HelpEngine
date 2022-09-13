#include "LowRenderer/Mesh.hpp"
#include "Resources/ResourceManager.hpp"
#include "LowRenderer/Renderer.hpp"
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <string>
#include <iostream>

using namespace LowRenderer;
using namespace Core::myMath;
using namespace Resources;
using namespace std;
using namespace Core::DataStructure;

Mesh::Mesh(Model* _model, int _shader) {
	model = _model;
	shaderProgram = _shader;
	MonoBehaviour();
}

Mesh::Mesh(Model* _model, int _shader, Material* _mat) {
	model = _model;
	material = _mat;
	shaderProgram = _shader;
	MonoBehaviour();
}

void Mesh::Start() {
	Renderer::meshList.push_back(this);
	Renderer::shaderProgram = shaderProgram;
}

void Mesh::Update() {
}

void Mesh::Render() {
	modelMatrix = gameObject->transform.GetModel();
	mat4x4 mvp = modelMatrix * Renderer::modelViewMatrix;

	if (material) {
		if (material->albedoTexture) {
			GLuint unit = 0;
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, material->albedoTexture->GetTexKey());
			glUniform1i(glGetUniformLocation(shaderProgram, "material.albedoTexture"), unit);

			glUniform1i(glGetUniformLocation(shaderProgram, "material.useTexture"), true);
		} else {
			glUniform1i(glGetUniformLocation(shaderProgram, "material.useTexture"), false);
		}
		glUniform3fv(glGetUniformLocation(shaderProgram, "material.albedoColor"), 1, &material->albedoColor.x);
		glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), material->shininess);
		glUniform3fv(glGetUniformLocation(shaderProgram, "material.specularColor"), 1, &material->specularColor.x);
	} else {
		glUniform1i(glGetUniformLocation(shaderProgram, "material.useTexture"), false);
		glUniform3f(glGetUniformLocation(shaderProgram, "material.albedoColor"), 1, 1, 1);
		glUniform3f(glGetUniformLocation(shaderProgram, "material.specularColor"), 0.8f, 0.8f, 0.8f);
		glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 32);
	}

	if (model) {
		glBindVertexArray(model->VAO);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_TRUE, &mvp.value[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_TRUE, &modelMatrix.value[0][0]);
		glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);
	}
}

void Mesh::DisplayGUI() {
	if(ImGui::CollapsingHeader("Mesh Renderer")) {
		ImGui::Text("Model : "); ImGui::SameLine();
		ImGui::Text(model->name.c_str());

		if (ImGui::BeginDragDropTarget()) {
			// Enable dropping textures onto materials.
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("4", ImGuiDragDropFlags_SourceAllowNullID)) {
				Model* droppedNode = *(Model**)payload->Data;
				model = droppedNode;
			}
			ImGui::EndDragDropTarget();
		}
		
		ImGui::Text("Material : "); ImGui::SameLine();
		ImGui::Text(material ? material->name.c_str() : "null");
		if (ImGui::BeginDragDropTarget()) {
			// Enable dropping textures onto materials.
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("1", ImGuiDragDropFlags_SourceAllowNullID)) {
				Material* droppedNode = *(Material**)payload->Data;
				material = droppedNode;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::SameLine();

		if (ImGui::Button("Delete"))
			material = nullptr;
	}	
}

void Mesh::Destroy() {
	Renderer::meshList.erase(std::remove(Renderer::meshList.begin(), Renderer::meshList.end(), this), Renderer::meshList.end());
}