#include "LowRenderer/Renderer.hpp"
#include <GLAD/includes/glad.h>
#include <GLFW/includes/glfw3.h>
#include <iostream>


using namespace LowRenderer;
using namespace Core::myMath;

Camera* Renderer::mainCamera;
std::vector<Light*> Renderer::lights;
std::vector<Mesh*> Renderer::meshList;
int Renderer::shaderProgram;
mat4x4 Renderer::modelViewMatrix;

void Renderer::Update() {
	if (mainCamera && meshList.size() > 0) {
		glUseProgram(shaderProgram);
		mainCamera->Render();

		int i = 0;
		for (Light* light : lights) {
			if (i >= 8)
				break;
			light->Render(i);
			i++;
		}
		glUniform1i(glGetUniformLocation(Renderer::shaderProgram, "lightCount"), i);

		for (Mesh* mesh : meshList) {
			mesh->Render();
		}
	}
}
