#pragma once
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "Core/App.hpp"
#include <string>


namespace CustomInterface
{
	inline int inspectorPosX = 0;
	inline int consolePosY = 0;

	inline void SetInspector()
	{
		inspectorPosX = Core::App::width - ImGui::GetWindowWidth();
		ImGui::SetWindowPos(ImVec2(inspectorPosX, 0));
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowSize().x, Core::App::height));
	}

	inline void SetHierarchie()
	{
		ImGui::SetWindowPos(ImVec2(0, 0));
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowSize().x, consolePosY));
	}

	inline void SetResourceManager()
	{
		ImGui::SetWindowPos(ImVec2(inspectorPosX - ImGui::GetWindowWidth() - 1, 0));
		ImGui::SetWindowSize(ImVec2(ImGui::GetWindowSize().x, consolePosY));
	}

	inline void SetConsole()
	{
		consolePosY = Core::App::height - ImGui::GetWindowHeight();
		//std::cout << consolePosY << "console pos y" << std::endl;
		ImGui::SetWindowPos(ImVec2(0, consolePosY));
		ImGui::SetWindowSize(ImVec2(inspectorPosX, ImGui::GetWindowHeight()));
	}
}



