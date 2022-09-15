#include <Resources/ResourceManager.hpp>
#include "Utils/Debug.hpp"
#include "Resources/Material.hpp"
#include "Interface/Interface.hpp"
#include <iostream>
#include <IMGUI/includes/imgui.h>
#include <IMGUI/includes/imgui_impl_opengl3.h>
#include <IMGUI/includes/imgui_impl_glfw.h>
#include "LowRenderer/Mesh.hpp"
#include "Physics/CollisionDisplay.hpp"
#include <thread>
#include <filesystem>
#include "Utils/Threading/PoolSystem.hpp"

using namespace Resources;
using namespace std;

unordered_map<string, Resource*> ResourceManager::resourceMap;
queue<Resource*> ResourceManager::needToBeBinded;

Resource* ResourceManager::Create(Resource* resource, const string& name, const string& path) {
	resource->name = name;
	resource->Load();
	if (!resource)
	{
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
		bool headerOpen = ImGui::CollapsingHeader((resource.first + (resource.second->isLoaded ? " true" : " false")).c_str());

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

void ResourceManager::InitResourceMap()
{
	std::string path = "resources";
	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		string filename = (strrchr(entry.path().u8string().c_str(), '\\') ? strrchr(entry.path().u8string().c_str(), '\\') + 1 : "");
		

		string extension = (strrchr(entry.path().u8string().c_str(), '.') ? strrchr(entry.path().u8string().c_str(), '.') + 1 : "folder");
		//cout << entry.path() << endl;

		if (extension == "folder") continue;
		if (extension == "png")
		{
			Texture* texture = new Texture(entry.path().u8string());
			texture->name = filename;
			resourceMap.emplace(filename, texture);
			continue;
		}
		if (extension == "obj")
		{
			Model* model = new Model(entry.path().u8string());
			model->name = filename;
			resourceMap.emplace(filename, model);
			continue;
		}
		if (extension == "frag")
		{
			Shader* model = new Shader(Shader::FRAGMENT, entry.path().u8string());
			model->name = filename;
			resourceMap.emplace(filename, model);
			continue;
		}
		if (extension == "vert")
		{
			Shader* model = new Shader(Shader::VERTEX, entry.path().u8string());
			model->name = filename;
			resourceMap.emplace(filename, model);
			continue;
		}
	}

	Shader* vert = ((Shader*)ResourceManager::Get("VertexShader.vert"));
	Shader* frag = ((Shader*)ResourceManager::Get("FragmentShader.frag"));
	if (!frag || !vert) return;
	ResourceManager::Create(new ShaderProgram(vert, frag), "ShaderProgram");
}

void ResourceManager::UpdateBinding()
{
	if (needToBeBinded.size() > 0)
	{
		needToBeBinded.front()->Bind();
		needToBeBinded.pop();
	}

	if (allResourcesareLoaded) return;
	allResourcesareLoaded = true;
	for (std::pair<string, Resource*> resource : resourceMap)
	{
		if (!resource.second->isLoaded)
			allResourcesareLoaded = false;
	}
	if (allResourcesareLoaded) pool.stopPool();
}

void ResourceManager::ReloadResources()
{
	auto begin = std::chrono::high_resolution_clock::now();

	if (asyncLoading) {

		for (int i = 0; i < 5; i++) {
			pool.registerThread(new NThread::Thread(pool, std::to_string(i)));
		}

		for (std::pair<string, Resource*> resource : resourceMap)
		{
			pool.registerTask(
				NThread::ResourceTask{
					[](Resource* r) {
						r->Load();
						needToBeBinded.push(r);
					}, resource.second
				}
			);
		}

		pool.registerTask(
			NThread::ResourceTask{
				[](Resource* r) {
					Shader* vert = ((Shader*)ResourceManager::Get("VertexShader.vert"));
					Shader* frag = ((Shader*)ResourceManager::Get("FragmentShader.frag"));
					if (!ResourceManager::Get("ShaderProgram")) return;
					while (!(frag->isLoaded && vert->isLoaded));
					needToBeBinded.push(ResourceManager::Get("ShaderProgram"));
				}, nullptr
			}
		);
	}
	else {
		for (std::pair<string, Resource*> resource : resourceMap) {
			resource.second->Load();
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
	float benchmark = elapsed.count() * 1e-9;

	if (asyncLoading) {
		std::cout << "[Async] Resources loading took: " << benchmark << " sec" << std::endl;
	}
	else {
		std::cout << "[Default] Resources loading took: " << benchmark << " sec" << std::endl;
	}
}
