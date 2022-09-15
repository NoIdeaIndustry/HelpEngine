#include "Core/Scene.hpp"
#include "LowRenderer/Camera.hpp"
#include "LowRenderer/Mesh.hpp"
#include "LowRenderer/Light.hpp"
#include "Resources/ResourceManager.hpp"
#include "Resources/Model.hpp"
#include "Components/CharacterMouvement.hpp"
#include "Core/App.hpp"
#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>
#include "Interface/Interface.hpp"
#include "Physics/Collision.hpp"
#include "Physics/RigidBody.hpp"
#include "Components/CameraBehaviour.hpp"
#include "Utils/Debug.hpp"
#include "Components/Respawn.hpp"

using namespace Core::DataStructure;
using namespace Core::myMath;
using namespace std;
using namespace LowRenderer;
using namespace Resources;

void LoadDefaultScene(Scene* scene) {
	
	// Initialize point light.
	GameObject& light = scene->Instantiate("Light");
	LowRenderer::Light* lightc = new LowRenderer::Light(1);
	lightc->linearAttenuation = 0.1f;
	lightc->quadraticAttenuation = 0.01f;
	lightc->color = Vec3(1, 0.95f, 0.7f);
	light.AddComponent(lightc);
	light.transform.position.y = 4;

	// Initialize point light.
	GameObject& light1 = scene->Instantiate("Light1");
	LowRenderer::Light* light1c = new LowRenderer::Light(1);
	light1c->linearAttenuation = 0.150f;
	light1c->quadraticAttenuation = 0.0f;
	light1c->color = Vec3(1, 0.95f, 0.7f);
	light1.AddComponent(light1c);
	light1.transform.position.x = 26;
	light1.transform.position.y = 2.7;
	light1.transform.position.z = 0;

	// Initialize point light.
	GameObject& light2 = scene->Instantiate("Light2");
	LowRenderer::Light* light2c = new LowRenderer::Light(1);
	light2c->linearAttenuation = 0.150f;
	light2c->quadraticAttenuation = 0.0f;
	light2c->color = Vec3(1, 0.95f, 0.7f);
	light2.AddComponent(light2c);
	light2.transform.position.x = 44.1f;
	light2.transform.position.y = 5.3f;
	light2.transform.position.z = 0;

	// Initialize point light.
	GameObject& light3 = scene->Instantiate("Light3");
	LowRenderer::Light* light3c = new LowRenderer::Light(1);
	light3c->linearAttenuation = 0.150f;
	light3c->quadraticAttenuation = 0.0f;
	light3c->color = Vec3(1, 0.95f, 0.7f);
	light3.AddComponent(light3c);
	light3.transform.position.x = 60.7f;
	light3.transform.position.y = 3.3f;

	//if (reloadResource ? ) reloadResource();

	light3.transform.position.z = 0;
	
	// Initialize a cube.
	GameObject& cube = scene->Instantiate("cube.obj");
	cube.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram"))));
	cube.AddComponent(new Physics::CubeCollider());
	cube.AddComponent(new Physics::RigidBody());
	cube.AddComponent(new Respawnable());
	cube.transform.position.x = 5;

	// Initialize a wall.
	GameObject& wall = scene->Instantiate("Wall");
	wall.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram"))));
	wall.AddComponent(new Physics::CubeCollider());
	wall.transform.position.z = -5;
	wall.transform.scale = Vec3(5, 5, 1);

	// Initialize a wall.
	GameObject& wall1 = scene->Instantiate("Wall1");
	wall1.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	wall1.AddComponent(new Physics::CubeCollider());
	wall1.transform.position = Vec3(72.5f, 5.8f, 0);
	wall1.transform.scale = Vec3(1.3f, 4.7f, 10.2f);

	// Initialize a wall.
	GameObject& wall2 = scene->Instantiate("Wall2");
	wall2.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	wall2.AddComponent(new Physics::CubeCollider());
	wall2.transform.position = Vec3(61.6f, 4.1f, 12);
	wall2.transform.scale = Vec3(9.5f, 7.4f, 1.9f);


	// Initialize player.
	GameObject& character = scene->Instantiate("Character");
	character.AddComponent(new CharacterMouvement());
	character.AddComponent(new Physics::SphereCollider(0.8f));
	character.AddComponent(new Physics::RigidBody());
	character.AddComponent(new Respawnable());

	GameObject& camHolder = scene->Instantiate("Camera Holder", &character);
	camHolder.AddComponent(new CameraBehaviour());

	GameObject& playerGraphics = scene->Instantiate("PlayerGraphics", &character);
	playerGraphics.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("goomba.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("goomba mat")));
	playerGraphics.transform.scale = Vec3(0.2f, 0.2f, 0.2f);
	playerGraphics.transform.position.y = -.8f;

	// Initialize ground.
	GameObject& ground = scene->Instantiate("Ground");
	ground.transform.scale = Vec3(10, 2, 10);
	ground.transform.position.y = -5;
	ground.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	ground.AddComponent(new Physics::CubeCollider());

	// Initialize ground.
	GameObject& ground1 = scene->Instantiate("Ground1");
	ground1.transform.position = Vec3(15.8f, -0.9f, 0);
	ground1.transform.scale = Vec3(3, 0.6f, 9.1f);
	ground1.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	ground1.AddComponent(new Physics::CubeCollider());

	// Initialize ground.
	GameObject& ground2 = scene->Instantiate("Ground2");
	ground2.transform.position = Vec3(26.1f, 1, 0.1);
	ground2.transform.rotation = Vec3(25.5, 0, 0);
	ground2.transform.scale = Vec3(4.4f, 1, 7.6f);
	ground2.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	ground2.AddComponent(new Physics::CubeCollider());

	// Initialize ground.
	GameObject& ground3 = scene->Instantiate("Ground3");
	ground3.transform.position = Vec3(45.4, 1.5f, 0);
	ground3.transform.rotation = Vec3(-23.6, 0, 0);
	ground3.transform.scale = Vec3(3.7f, 1, 6.1f);
	ground3.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	ground3.AddComponent(new Physics::CubeCollider());

	// Initialize ground.
	GameObject& ground4 = scene->Instantiate("Ground4");
	ground4.transform.position = Vec3(62.8f, 2, 0);
	ground4.transform.rotation = Vec3(-0, 0, 0);
	ground4.transform.scale = Vec3(8.9f, 1, 10.4f);
	ground4.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("cube.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram")), (Material*)ResourceManager::Get("Ground Mat")));
	ground4.AddComponent(new Physics::CubeCollider());


	// Initialize a sphere.
	GameObject& sphere = scene->Instantiate("Sphere");
	sphere.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("sphere.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram"))));
	sphere.AddComponent(new Physics::CubeCollider());
	sphere.AddComponent(new Physics::RigidBody());
	sphere.AddComponent(new Respawnable());
	sphere.transform.position = Vec3(43.4, 6.5f, 4);

	// Initialize a sphere.
	GameObject& sphere1 = scene->Instantiate("Sphere1");
	sphere1.AddComponent(new LowRenderer::Mesh((Model*)ResourceManager::Get("sphere.obj"),
		((ShaderProgram*)ResourceManager::Get("ShaderProgram"))));
	sphere1.AddComponent(new Physics::CubeCollider());
	sphere1.AddComponent(new Physics::RigidBody());
	sphere1.AddComponent(new Respawnable());
	sphere1.transform.position = Vec3(25.4, 6.5f, -4);

	// Initialize cam.
	GameObject& cam = scene->Instantiate("Main Camera", &camHolder);
	cam.AddComponent(new LowRenderer::Camera());
	cam.transform.position.y = 4;
	cam.transform.rotation.x = 20;
	cam.transform.position.z = -18;
}


void Scene::Start() {	
	currentScene = this;
	LoadDefaultScene(this);
	for (GameObject* object : gameObjects) {
		object->Start();
	}
}

void Scene::Update() {
	Debug::Log::Update();

	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->isDestroyed) {
			if (!gameObjects[i]->GetParent()) {
				rootGameObjects.erase(std::remove(rootGameObjects.begin(), rootGameObjects.end(), gameObjects[i]), rootGameObjects.end());
			}
			delete gameObjects[i];
			gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObjects[i]), gameObjects.end());
			i--;
		}
	}

	for (GameObject* object : gameObjects) {
		object->Update();
	}
	Physics::Collision::UpdateCollision();

	DisplayGUI();
}

void Scene::Destroy() {
	for (GameObject* object : rootGameObjects) {
		object->Destroy();
		delete object;
	}
	rootGameObjects.clear();
	gameObjects.clear();
}

void Scene::DisplayGUI() {
	static GameObject* selected;

	ImGui::Begin("Scene Graph", 0, ImGuiWindowFlags_NoMove);
	CustomInterface::SetHierarchie();
	ImGui::SetWindowFontScale(1.2f);


	if (ImGui::Button("New GameObject")) {
		selected = &Instantiate("GameObject");
	}

	
	for (GameObject* objects : rootGameObjects) {
		objects->ShowInHierarchy(&selected);
	}
	

	ImGui::End();

	if (selected && !selected->isDestroyed)
		selected->DisplayGUI();
	else {
		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);
		CustomInterface::SetInspector();
		ImGui::End();
	}

}

GameObject& Scene::Instantiate(string _name, Vec3 _position, Vec3 _rotation, Vec3 _scale) {
	GameObject* newObject = new GameObject();

	newObject->name = _name + "##" + to_string(gameObjects.size());
	newObject->transform.position = _position;
	newObject->transform.rotation = _rotation;
	newObject->transform.scale = _scale;
	newObject->transform.gameObject = newObject;

	gameObjects.push_back(newObject);
	rootGameObjects.push_back(newObject);
	return *gameObjects.at(gameObjects.size() - 1);
}

GameObject& Scene::Instantiate(GameObject* object) {
	object->transform.gameObject = object; 
	gameObjects.push_back(object);
	rootGameObjects.push_back(object);
	return *gameObjects.at(gameObjects.size() - 1);
}

GameObject& Scene::Instantiate(std::string _name, GameObject* parent) {
	GameObject* newObject = new GameObject();

	newObject->name = _name + "##" + to_string(gameObjects.size());
	newObject->transform.gameObject = newObject;
	if (parent) {
		parent->AddChildren(newObject);
	} else {
		rootGameObjects.push_back(newObject);
	}

	gameObjects.push_back(newObject);
	return *gameObjects.at(gameObjects.size() - 1);
}

