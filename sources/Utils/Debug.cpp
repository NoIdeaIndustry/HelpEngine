#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>

#include "Utils/Debug.hpp"
#include "Resources/ResourceManager.hpp"
#include "Interface/Interface.hpp"

using namespace Core::Debug;
using namespace std;

void Log::Print(string message, logType type) {
	string prefix;
	switch (type)
	{
	case Core::Debug::Log::Message:
		prefix = 'M';
		break;
	case Core::Debug::Log::Warning:
		prefix = 'W';
		break;
	case Core::Debug::Log::Error:
		prefix = 'E';
		break;
	default:
		break;
	}


	logs.push_back(prefix + message);
}

void Log::Update() {

	ImGui::Begin("Console", 0, ImGuiWindowFlags_NoMove);
	CustomInterface::SetConsole();

	if (ImGui::Button("Clear")) {
		logs.clear();
	}

	for (string log : logs) {
		ImGui::Separator();
		switch (log[0])
		{
		case 'M': if(messageIcon && messageIcon->isLoaded) ImGui::Image((ImTextureID)messageIcon->GetTexKey(), ImVec2(40, 40), ImVec2(0, 1), ImVec2(1, 0), ImVec4(0.6f, 0.6f, 0.6f, 1)); break;
		case 'E': if(errorIcon && errorIcon->isLoaded) ImGui::Image((ImTextureID)errorIcon->GetTexKey(), ImVec2(40, 40), ImVec2(0, 1), ImVec2(1, 0)); break;
		case 'W': if(warningIcon && warningIcon->isLoaded) ImGui::Image((ImTextureID)warningIcon->GetTexKey(), ImVec2(50, 50), ImVec2(0, 1), ImVec2(1, 0)); break;
		default: break;
		}

		ImGui::SameLine();
		ImGui::Text(log.substr(1).c_str());
	}
	ImGui::Separator();
	ImGui::End();
}

void Log::Init() {
	messageIcon = (Resources::Texture*)Resources::ResourceManager::Get("Message");
	warningIcon = (Resources::Texture*)Resources::ResourceManager::Get("Warning");
	errorIcon = (Resources::Texture*)Resources::ResourceManager::Get("Error");
}

string Log::GetFunctionName(const string& macro) {
	string res;
	int i = 0;
	bool end = false;
	for (char c : macro) {
		if (c == '@') {
			if (end)
				break;

			res.insert(res.begin() + i, ':');
			res.insert(res.begin() + i, ':');
			end = true;
			i = 0;
			continue;
		}
		
		if (c == '?') {
			end = false;
			continue;
		}

		end = false;
		res.insert(res.begin() + i, c);

		i++;
	}

	res.replace(res.end() - 2, res.end(), "()");
	return res;
}