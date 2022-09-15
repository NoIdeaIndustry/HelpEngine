#pragma once

#include <string>
#include <unordered_map>
#include <queue>
#include "Utils/Threading/PoolSystem.hpp"
#include <Resources/Resource.hpp>

namespace Resources
{
	class ResourceManager
	{
	public :
		inline static bool asyncLoading = false;


		static void DisplayGUI();
	
		static Resource* Create(Resource* resource, const std::string& name, const std::string& path);
		static Resource* Create(Resource* resource, const std::string& name);

		static Resource* Get(const std::string& name);
		//static void Delete(const std::string& name);
		static void Clear();
		static void ReloadResources();
		static void UpdateBinding();
		static void InitResourceMap();

	private :
		static std::unordered_map<std::string, Resource*> resourceMap;
		static std::queue<Resource*> needToBeBinded;
		inline static NThread::Pool pool;
		inline static bool allResourcesareLoaded;
	};
}

