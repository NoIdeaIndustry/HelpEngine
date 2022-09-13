#include <Resources/ResourceManager.hpp>
#include "Utils/Debug.hpp"
#include "Resources/Material.hpp"
#include "Interface/Interface.hpp"
#include <iostream>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "LowRenderer/Mesh.hpp"
#include "Physics/CollisionDisplay.hpp"
#include <filesystem>

using namespace Resources;
using namespace std;

unordered_map<string, Resource*> ResourceManager::resourceMap;
queue<Resource*> ResourceManager::needToBeBinded;

Resource* ResourceManager::Create(Resource* resource, const string& name, const string& path) {
	resource->name = name;
	resource->Load(path);

	if (!resource) {
		DEBUG_LOGERROR("Resource loading failed.");
		return nullptr;
	}
	resourceMap.emplace(name, resource);
	return resource;
}

Resource* ResourceManager::Create(Resource* resource, const string& name) {
	resource->name = name;
	resourceMap.emplace(name, resource);
	return resource;
}

Resource* ResourceManager::Get(const string& name) {
	if (resourceMap.find(name) != resourceMap.end()) {
		return resourceMap[name];
	}
	return nullptr;
}

void ResourceManager::Clear() {
	//std::cout << "Clearing all resources" << std::endl;
	for (std::pair<string, Resource*> resource : resourceMap) {
		resource.second->Unload();
		//std::cout << resource.first << std::endl;
		delete resource.second;
	}
}

void ResourceManager::DisplayGUI() {
	ImGui::Begin("Resources", 0, ImGuiWindowFlags_NoMove);
	CustomInterface::SetResourceManager();
	
	ImGui::OpenPopupOnItemClick("Add Resource");

	if (ImGui::Button("New Material")) {
		Create(new Resources::Material(nullptr, Core::myMath::Vec3(1, 1, 1), 32), ("new mat##" + to_string(resourceMap.size())).c_str());
	}

	int index = 0;
	for (std::pair<string, Resource*> resource : resourceMap) {
		if ((int)resource.second->type == 2 || (int)resource.second->type == 3) {
			continue;
		}

		bool headerOpen = ImGui::CollapsingHeader(resource.first.c_str());

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
			void** ptr = new void* (resource.second);
			ImGui::SetDragDropPayload(to_string((int)resource.second->type).c_str(), ptr, sizeof(resource.second));
			ImGui::Text(resource.second->name.c_str());
			ImGui::EndDragDropSource();
			delete ptr;
		}

		if (headerOpen) {
			resource.second->DisplayGUI(index);
			index++;
		}
	}

	ImGui::End();
}

void ResourceManager::InitResourceMap() {
	//std::string path = "resources";
	//for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	//{
	//	//std::cout << entry.path().filename() << std::endl;
	//}
	resourceMap.emplace("Resources\\Textures\\boo.png", nullptr);
}

void ResourceManager::UpdateBinding() {

}

void ResourceManager::ReloadResources() {
	for (std::pair<string, Resource*> resource : resourceMap) {

	}
}
