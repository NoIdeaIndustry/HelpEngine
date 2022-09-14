#include "Core/Scene.hpp"
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "LowRenderer/Camera.hpp"
#include "LowRenderer/Light.hpp"
#include "LowRenderer/Mesh.hpp"
#include "Interface/Interface.hpp"
#include "Resources/ResourceManager.hpp"
#include "Components/CharacterMouvement.hpp"
#include "Physics/Collision.hpp"
#include "Components/Respawn.hpp"

using namespace Core::DataStructure;
using namespace Core::myMath;
using namespace std;
using namespace Resources;


void GameObject::Start() {
	transform.Start();

	for (MonoBehaviour* component : componentsBuffer) {
		components.push_back(component);
	}
	componentsBuffer.clear();

	for (MonoBehaviour* component : components) {
		component->Start();
	}
}

void GameObject::Update() {
	for (MonoBehaviour* component : componentsBuffer) {
		components.push_back(component);
		component->Start();
	}
	componentsBuffer.clear();

	transform.Update();

	for (MonoBehaviour* component : components) {
		component->Update();
	}
}

void GameObject::DisplayGUI() {
	ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);
	CustomInterface::SetInspector();

	std::string key = strrchr((name).c_str(), '#');
	std::string _name = name.substr(0, name.size() - key.size() - 1);
	char inputBuffer[128];

#pragma warning(suppress : 4996)
	std::strcpy(inputBuffer, _name.c_str());
	ImGui::InputText("##Name", inputBuffer, 128);
	name = inputBuffer;
	name += '#' + key;
	
	if (name == "") name = " ";

	ImGui::Separator();
	ImGui::NewLine();

	transform.DisplayGUI();

	for (MonoBehaviour* component : components) {
		ImGui::PushItemWidth(150);
		component->DisplayGUI();
		ImGui::PopItemWidth();
	}

	
	if (ImGui::BeginPopupContextItem("Compononet List")) {
		if (ImGui::Selectable("Character Mouvement")) { AddComponent(new CharacterMouvement()); }
		if(ImGui::Selectable("Respawnable")) { AddComponent(new Respawnable()); }

		ImGui::Separator();

		if (ImGui::Selectable("Camera")) { AddComponent(new LowRenderer::Camera()); }
		if (ImGui::Selectable("Light")) { AddComponent(new LowRenderer::Light(0)); }
		if (ImGui::Selectable("Mesh")) { AddComponent(new LowRenderer::Mesh(((Model*)ResourceManager::Get("Cube")),((ShaderProgram*)ResourceManager::Get("ShaderProgram")) )); }

		ImGui::Separator();

		if (ImGui::Selectable("Sphere Collider")) { AddComponent(new Physics::SphereCollider(1)); }
		if (ImGui::Selectable("Cube Collider")) { AddComponent(new Physics::CubeCollider()); }
		if (ImGui::Selectable("RigidBody")) { AddComponent(new Physics::RigidBody()); }
		//ImGui::SetNextItemWidth(-FLT_MIN);
		
		ImGui::EndPopup();
	}

	if (ImGui::Button("Add Component")) {
		ImGui::OpenPopup("Compononet List");
	}

	ImGui::End();
}

void GameObject::Destroy() {
	isDestroyed = true;
	for (MonoBehaviour* component : components) {
		component->Destroy();
	}
	for (MonoBehaviour* component : components) {
		delete component;
	}
	for (GameObject* child : children) {
		child->Destroy();
	}
	if (parent) {
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());
	}

}

void GameObject::ShowInHierarchy(GameObject** selected) {
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
	if (*selected == this)
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	if (children.size() <= 0)
		nodeFlags |= ImGuiTreeNodeFlags_Leaf;

	ImGui::AlignTextToFramePadding();


	bool isOpened = ImGui::TreeNodeEx(name.c_str(), nodeFlags);
	if (ImGui::BeginPopupContextItem("GameObject Popup")) {
		if (ImGui::Selectable("Empty GameObject")) {
			Scene::currentScene->Instantiate("Child", this);
		}

		if (ImGui::Button("Delete")) {
			Destroy();
		}
		ImGui::EndPopup();
	}

	if (ImGui::IsItemClicked(1)) {
		ImGui::OpenPopup("GameObject Popup");
	}

	if (ImGui::IsItemClicked()) {
		*selected = this;
	}

	if (isOpened) {
		for (GameObject* object : children) {
			object->ShowInHierarchy(selected);
		}
		ImGui::TreePop();
	}
}

void GameObject::AddComponent(MonoBehaviour* component) {
	component->gameObject = this;
	componentsBuffer.push_back(component);
}

GameObject* GameObject::GetParent() {
	return parent;
}

vector<GameObject*> GameObject::GetChildren() {
	return children;
}

void GameObject::AddChildren(GameObject* object) {
	object->parent = this;
	children.push_back(object);
}

void MonoBehaviour::Start()       { }
void MonoBehaviour::Update()      { }
void MonoBehaviour::DisplayGUI()  { }
void MonoBehaviour::Destroy()     { }

void Transform::Start() {
}

void Transform::Update() {
}

void Transform::DisplayGUI() {
	if (ImGui::CollapsingHeader("Transform")) {
		ImGui::DragFloat3("Position", &position.x, 0.1f, -100, 100);
		ImGui::DragFloat3("Rotation", &rotation.x, 0.1f, -180, 180);
		ImGui::DragFloat3("Scale", &scale.x, 0.1f, -100, 100);
	}
}

mat4x4 Transform::GetModel() {
	mat4x4 localModel = mat4x4::Scale(scale) * mat4x4::Rotation(rotation) * mat4x4::Translation(position);
	if (gameObject->GetParent())
		localModel = localModel * gameObject->GetParent()->transform.GetModel();
	return localModel;
}

Vec3 Transform::GetGlobalPosition() {
	mat4x4 localModel = mat4x4::Scale(scale) * mat4x4::Rotation(rotation) * mat4x4::Translation(position);
	if (gameObject->GetParent())
		localModel = localModel * gameObject->GetParent()->transform.GetModel();
	
	return Vec3(localModel.value[0][3], localModel.value[1][3], localModel.value[2][3]);
}

