#include "Physics/Collision.hpp"
#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>
#include "Resources/Model.hpp"
#include "Utils/Debug.hpp"
#include "Physics/CollisionDisplay.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Utils/Time.hpp"

using namespace Resources;
using namespace Core::myMath;
using namespace Physics;
using namespace CollisionDisplay;
using namespace LowRenderer;

Vec3 SphereCollider::FindFurthestPoint(const Vec3& direction) const {
	return gameObject->transform.GetGlobalPosition() + (direction.Normalized() * radius);
}

SphereCollider::SphereCollider(float _radius) : radius(_radius) {

}

void SphereCollider::Render() const {
	if (!DrawCollider) {
		return;
	}
	glUseProgram(Renderer::shaderProgram->GetProgram());
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mat4x4 model = mat4x4::Scale(Vec3(radius, radius, radius)) * gameObject->transform.GetModel();
	mat4x4 mvp = model * Renderer::modelViewMatrix;

	glUniform1i(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "material.useTexture"), false);
	glUniform3f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "material.albedoColor"), 0, 1, 0);

	glBindVertexArray(CollisionMesh::Sphere.VAO);
	glUniformMatrix4fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "mvp"), 1, GL_TRUE, &mvp.value[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "model"), 1, GL_TRUE, &model.value[0][0]);
	glDrawElements(GL_TRIANGLES, CollisionMesh::Sphere.indexCount, GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SphereCollider::Start() {
	Collision::colliders.push_back(this);
	rigidBody = gameObject->GetComponent<RigidBody>();
}

void SphereCollider::Update() {
}

void SphereCollider::Destroy() {
	Collision::colliders.erase(std::remove(Collision::colliders.begin(), Collision::colliders.end(), this), Collision::colliders.end());
}

void SphereCollider::DisplayGUI() {
	if (ImGui::CollapsingHeader("Sphere Collider")) {
		ImGui::Checkbox("Draw Collider", &DrawCollider);
		ImGui::DragFloat("Radius", &radius, 0.01f, 0.01f);
	}
}


Vec3 CubeCollider::FindFurthestPoint(const Vec3& direction) const {
	Vec3 res;
	float max = -FLT_MAX;

	for (Vec3 vertex : vertices) {
		Vec3 globalVertex = (mat4x4::Scale(Vec3(size.x, size.y, size.z)) * gameObject->transform.GetModel() * Vec4(vertex, 1)).toVec3();
		float dot = direction * globalVertex;

		if (dot > max) {
			max = dot;
			res = globalVertex;
		}
	}
	return res;
}

void CubeCollider::Start() {
	vertices.push_back(Vec3(1, 1, 1));
	vertices.push_back(Vec3(1, -1, 1));
	vertices.push_back(Vec3(-1, -1, 1));
	vertices.push_back(Vec3(-1, 1, 1));

	vertices.push_back(Vec3(1, 1, -1));
	vertices.push_back(Vec3(1, -1, -1));
	vertices.push_back(Vec3(-1, -1, -1));
	vertices.push_back(Vec3(-1, 1, -1));

	size = Vec3(1, 1, 1);

	Collision::colliders.push_back(this);
	rigidBody = gameObject->GetComponent<RigidBody>();
}

void CubeCollider::Update() {
}

void CubeCollider::Render() const {
	if (!DrawCollider) {
		return;
	}
	glUseProgram(Renderer::shaderProgram->GetProgram());
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mat4x4 model = mat4x4::Scale(Vec3(size.x, size.y, size.z)) * gameObject->transform.GetModel();
	mat4x4 mvp = model * Renderer::modelViewMatrix;

	glUniform1i(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "material.useTexture"), false);
	glUniform3f(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "material.albedoColor"), 0, 1, 0);

	glBindVertexArray(CollisionMesh::Cube.VAO);
	glUniformMatrix4fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "mvp"), 1, GL_TRUE, &mvp.value[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(Renderer::shaderProgram->GetProgram(), "model"), 1, GL_TRUE, &model.value[0][0]);
	glDrawElements(GL_TRIANGLES, CollisionMesh::Cube.indexCount, GL_UNSIGNED_INT, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CubeCollider::Destroy() {
	Collision::colliders.erase(std::remove(Collision::colliders.begin(), Collision::colliders.end(), this), Collision::colliders.end());
}

void CubeCollider::DisplayGUI() {
	if (ImGui::CollapsingHeader("Cube Collider")) {
		ImGui::Checkbox("Draw Collider", &DrawCollider);
		ImGui::DragFloat3("Size", &size.x, 0.01f, 0.01f);
	}
}
