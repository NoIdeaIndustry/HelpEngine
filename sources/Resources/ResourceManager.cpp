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
	resourceMap.clear();

	while (!needToBeBinded.empty())
	{
		needToBeBinded.pop();
	}
	pool.stopPool();
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

		//bool headerOpen = ImGui::CollapsingHeader((resource.first /* + " " + (resource.second->isLoaded ? "true" : "false")*/).c_str());

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
	allResourcesareLoaded = false;
	std::string path = "resources";
	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		string filename = (strrchr(entry.path().u8string().c_str(), '\\') ? strrchr(entry.path().u8string().c_str(), '\\') + 1 : "");
		

		string extension = (strrchr(entry.path().u8string().c_str(), '.') ? strrchr(entry.path().u8string().c_str(), '.') + 1 : "folder");
		cout << entry.path() << endl;

		if (extension == "folder") continue;
		if (extension == "png" || extension == "jpg")
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
			Shader* shader = new Shader(Shader::FRAGMENT, entry.path().u8string());
			shader->name = filename;
			resourceMap.insert(resourceMap.begin(), pair<string, Resource*>(filename, shader));
			continue;
		}
		if (extension == "vert")
		{
			Shader* shader = new Shader(Shader::VERTEX, entry.path().u8string());
			shader->name = filename;
			resourceMap.insert(resourceMap.begin(), pair<string, Resource*>(filename, shader));
			continue;
		}
	}

	Shader* vert = ((Shader*)ResourceManager::Get("VertexShader.vert"));
	Shader* frag = ((Shader*)ResourceManager::Get("FragmentShader.frag"));
	if (!frag || !vert) return;
	ResourceManager::Create(new ShaderProgram(vert, frag), "ShaderProgram");

	ResourceManager::Create(new Material(((Texture*)ResourceManager::Get("goomba.png")), Core::myMath::Vec3(1, 1, 1), 1), "goomba mat");
	ResourceManager::Create(new Material(((Texture*)ResourceManager::Get("sol.png")), Core::myMath::Vec3(1, 1, 1), 1), "ground mat");
	ResourceManager::Create(new Material(((Texture*)ResourceManager::Get("wall.jpg")), Core::myMath::Vec3(1, 1, 1), 1), "wall mat");
	ResourceManager::Create(new Material(nullptr, Core::myMath::Vec3(1, 0, 0), 3), "cube mat");
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
		{
			allResourcesareLoaded = false; 
			break;
		}
	}
	if (allResourcesareLoaded)
	{
		loadingChronoEnd = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(loadingChronoEnd - loadingChronoStart);
		float benchmark = elapsed.count() * 1e-9;
		if (asyncLoading)
		{
			DEBUG_LOG("[MultiThread] Resources loading took: " + to_string(benchmark * 1000) + " miliseconds");
		}
		else
		{
			DEBUG_LOG("[MonoThread] Resources loading took: " + to_string(benchmark * 1000) + " miliseconds");
		}
	

		pool.stopPool();
	}
}

void ResourceManager::ReloadResources()
{
	loadingChronoStart = std::chrono::high_resolution_clock::now();


	

	if (asyncLoading)
	{
		pool.startPool();

		pool.getPool().clear();
		for (int i = 0; i < 3; i++) {
			pool.registerThread(new NThread::Thread(pool, std::to_string(i)));
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
			});

		for (std::pair<string, Resource*> resource : resourceMap)
		{
			/*this_thread::sleep_for(chrono::milliseconds(300)); */
			if (resource.second->type == Resource::ResourceType::R_SHADERPROGRAM) continue;

			pool.registerTask(
				NThread::ResourceTask {
					[](Resource* r) {
						r->Load();
						queueMutex.lock();
						needToBeBinded.push(r);
						queueMutex.unlock();
					}, resource.second
				}
			);
		}
		

		
	}
	else
	{
		for (std::pair<string, Resource*> resource : resourceMap)
		{
			if (resource.second->type == Resource::ResourceType::R_SHADERPROGRAM) continue;
			resource.second->Load();
			needToBeBinded.push(resource.second);
		}
		needToBeBinded.push(ResourceManager::Get("ShaderProgram"));

		
	}


	
	//pool.stopPool();
}
