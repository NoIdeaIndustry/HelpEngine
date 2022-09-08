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

using namespace Resources;
using namespace std;

unordered_map<string, Resource*> ResourceManager::resourceMap;

Resource* ResourceManager::Create(Resource* resource, const string& name, const string& path)
{
	resource->name = name;
	resource->Load(path);
	if (!resource)
	{
		DEBUG_LOGERROR("Resource loading failed.");
		return nullptr;
	}
	resourceMap.emplace(name, resource);
	return resource;
}

Resource* ResourceManager::Create(Resource* resource, const string& name)
{
	resource->name = name;
	resourceMap.emplace(name, resource);
	return resource;
}

Resource* ResourceManager::Get(const string& name)
{

	if (resourceMap.find(name) != resourceMap.end())
	{
		return resourceMap[name];
	}
	return nullptr;
}

void ResourceManager::Clear()
{
	//std::cout << "Clearing all resources" << std::endl;
	for (std::pair<string, Resource*> resource : resourceMap)
	{
		resource.second->Unload();
		//std::cout << resource.first << std::endl;
		delete resource.second;
	}
}

void ResourceManager::DisplayGUI()
{
	ImGui::Begin("Resources", 0, ImGuiWindowFlags_NoMove);
	CustomInterface::SetResourceManager();
	
	ImGui::OpenPopupOnItemClick("Add Resource");
	if (ImGui::Button("New Material"))
	{
		Create(new Resources::Material(nullptr, Core::myMath::Vec3(1, 1, 1), 32), ("new mat##" + to_string(resourceMap.size())).c_str());
	}

	int index = 0;
	for (std::pair<string, Resource*> resource : resourceMap)
	{
		if ((int)resource.second->type == 2 || (int)resource.second->type == 3)
			continue;

		bool headerOpen = ImGui::CollapsingHeader(resource.first.c_str());

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			void** ptr = new void* (resource.second);
			ImGui::SetDragDropPayload(to_string((int)resource.second->type).c_str(), ptr, sizeof(resource.second));
			ImGui::Text(resource.second->name.c_str());
			ImGui::EndDragDropSource();
			delete ptr;
		}

		if (headerOpen)
		{
			resource.second->DisplayGUI(index);
			index++;
		}
	}

	ImGui::End();
}

void ResourceManager::ReloadResources()
{
	ResourceManager::Create(new Model(), "Blaziken", "Resources\\Objects\\blaziken.obj");
	ResourceManager::Create(new Model(), "Bidoof", "Resources\\Objects\\Bidoof.obj");
	ResourceManager::Create(new Model(), "Cube", "Resources\\Objects\\cube.obj");
	ResourceManager::Create(new Model(), "Sphere", "Resources\\Objects\\sphere.obj");
	ResourceManager::Create(new Model(), "Boo", "Resources\\Objects\\boo.obj");
	ResourceManager::Create(new Model(), "Goomba", "Resources\\Objects\\goomba.obj");
	ResourceManager::Create(new Model(), "Maskass", "Resources\\Objects\\maskass.obj");


	CollisionDisplay::CollisionMesh::InitSphereMesh();
	CollisionDisplay::CollisionMesh::InitCubeMesh();

	Texture::InitSampler();
	ResourceManager::Create(new Texture(), "BippaDh", "Resources\\Textures\\BippaDh.png");
	ResourceManager::Create(new Texture(), "dog", "Resources\\Textures\\sample2.png");
	ResourceManager::Create(new Texture(), "Blaziken Texture", "Resources\\Textures\\BlazikenTexture.png");
	ResourceManager::Create(new Texture(), "Goomba Texture", "Resources\\Textures\\goomba.png");
	ResourceManager::Create(new Texture(), "Boo Texture", "Resources\\Textures\\boo.png");
	ResourceManager::Create(new Texture(), "Maskass Texture", "Resources\\Textures\\heyho_tex_hr.png");
	ResourceManager::Create(new Texture(), "Ground Texture", "Resources\\Textures\\sol.png");

	ResourceManager::Create(new Texture(), "Message", "Resources\\Textures\\Message_Icone.png");
	ResourceManager::Create(new Texture(), "Error", "Resources\\Textures\\Error_Icone.png");
	ResourceManager::Create(new Texture(), "Warning", "Resources\\Textures\\Warning_Icone.png");



	ResourceManager::Create(new Material((Texture*)ResourceManager::Get("Goomba Texture"), Core::myMath::Vec3(1, 1, 1), 2), "goomba mat");
	ResourceManager::Create(new Material((Texture*)ResourceManager::Get("Ground Texture"), Core::myMath::Vec3(1, 1, 1), 2), "Ground Mat");

	
}
