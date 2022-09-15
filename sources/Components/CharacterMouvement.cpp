#include "Components/CharacterMouvement.hpp"
#include "Utils/Debug.hpp"
#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>
#include "Utils/Input.hpp"
#include <string>

using namespace Core::myMath;

void CharacterMouvement::Update() {
	Vec3 direction = Vec3(Vec2(0, 1).Rotate(Vec2(), -gameObject->transform.rotation.y * (mPI / 180)), 0);
	Vec3 forward = Vec3(direction.x, 0, direction.y);
	Vec3 left = Vec3(forward.z, 0, -forward.x);

	Vec3 move = forward * Input::GetVerticalAxis() * movementSpeed + left * Input::GetHorizontalAxis() * movementSpeed;
	rb->velocity = Lerp(rb->velocity, Vec3(move.x, rb->velocity.y, move.z), 0.2f);

	if (Input::IsKeyDown(Input::newKeyJump) && rb->isGrounded){
		rb->AddForce(Vec3(0, jumpHeight, 0));
	}

	if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2)){
		gameObject->transform.rotation.y += Input::GetMouseDelta().x * 0.2f;
	}

	
}  

void CharacterMouvement::Start() {
	rb = gameObject->GetComponent<Physics::RigidBody>();
	if (!rb) DEBUG_LOGWARNING("No rigidbody in character controller");
}

void CharacterMouvement::DisplayGUI() {
	if(ImGui::CollapsingHeader("Character Mouvement")) {
		ImGui::DragFloat("Movement Speed", &movementSpeed);
		ImGui::DragFloat("Jump Height", &jumpHeight);
	}
} 