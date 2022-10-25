#include "Physics/RigidBody.hpp"
#include "Physics/Collision.hpp"
#include "Utils/Time.hpp"
#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>

using namespace Physics;
using namespace Core::myMath;

void RigidBody::Start() {
	velocity = Vec3();
	Collider* col = gameObject->GetComponent<SphereCollider>();
	if(!col) col = gameObject->GetComponent<CubeCollider>();
	
	if (col) {
		col->rigidBody = this;
	}
	
	Collision::rigidBodies.push_back(this);
}

void RigidBody::Destroy() {
	Collider* col = gameObject->GetComponent<SphereCollider>();
	if (!col) col = gameObject->GetComponent<CubeCollider>();

	if (col) {
		col->rigidBody = nullptr;
	}
	Collision::rigidBodies.erase(std::remove(Collision::rigidBodies.begin(), Collision::rigidBodies.end(), this), Collision::rigidBodies.end());
}

void RigidBody::Update() {
	velocity += gravity * gravityScale * Time::deltaTime;
	velocity *= 1 - friction;
}

void RigidBody::AddForce(Vec3 force, bool isContinuous) {
	velocity += force * (isContinuous ? Time::deltaTime : 1);
}

void RigidBody::DisplayGUI() {
	if (ImGui::CollapsingHeader("RigidBody")) {
		ImGui::DragFloat3("Velocity", &velocity.x, 0.02f);
		ImGui::DragFloat("Friction", &friction, 0.01f, 0, 1);
		ImGui::DragFloat("Gravity Scale", &gravityScale, 0.01f);
		ImGui::Separator();
		ImGui::DragFloat3("Global Gravity", &gravity.x, 0.02f);
		ImGui::Checkbox("Is Grounded", &isGrounded);
	}
}
