#pragma once
#include <string>
#include <Resources/Resource.hpp>
#include <unordered_map>


namespace Resources
{

class ResourceManager
{
public :
	static void DisplayGUI();
	
	static Resource* Create(Resource* resource, const std::string& name, const std::string& path);
	static Resource* Create(Resource* resource, const std::string& name);

	static Resource* Get(const std::string& name);
	//static void Delete(const std::string& name);
	static void Clear();

private :
	static std::unordered_map<std::string, Resource*> resourceMap;
};

}

