#include "Interface/Theme.hpp"

namespace CustomInterface::CustomTheme
{
	void Theme::LoadDefaultTheme(const bool& s_EraseData)
	{
		if (s_EraseData)
		{
			p_TextColor = ImColor(255, 255, 255);
			p_MainColor = ImColor(235, 66, 66);
			p_BackgroundColor = ImColor(33, 36, 43);
			p_FillArea = ImColor(51, 56, 69);
		}

		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 0.58f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(p_BackgroundColor.x, p_BackgroundColor.y, p_BackgroundColor.z, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(p_BackgroundColor.x, p_BackgroundColor.y, p_BackgroundColor.z, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(p_FillArea.x, p_FillArea.y, p_FillArea.z, p_FillArea.w + .1f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.68f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.45f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(p_FillArea.x, p_FillArea.y, p_FillArea.z, 0.57f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(p_FillArea.x, p_FillArea.y, p_FillArea.z, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.85f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.90f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);

		style.Colors[ImGuiCol_CheckMark] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.90f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.90f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.50f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.80f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.86f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);

		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.20f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);

		style.Colors[ImGuiCol_Tab] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);


		style.Colors[ImGuiCol_PlotLines] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.43f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(p_BackgroundColor.x, p_BackgroundColor.y, p_BackgroundColor.z, 0.92f);
	}

	void Theme::LoadGoldTheme(const bool& s_EraseData)
	{
		if (s_EraseData)
		{
			p_TextColor = ImColor(255, 255, 255);
			p_MainColor = ImColor(234, 157, 52);
			p_BackgroundColor = ImColor(33, 36, 43);
			p_FillArea = ImColor(51, 56, 69);
		}

		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_Text] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 0.58f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(p_BackgroundColor.x, p_BackgroundColor.y, p_BackgroundColor.z, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(p_BackgroundColor.x, p_BackgroundColor.y, p_BackgroundColor.z, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(p_FillArea.x, p_FillArea.y, p_FillArea.z, p_FillArea.w + .1f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.68f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.45f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(p_FillArea.x, p_FillArea.y, p_FillArea.z, 0.57f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(p_FillArea.x, p_FillArea.y, p_FillArea.z, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.85f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.90f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);

		style.Colors[ImGuiCol_CheckMark] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.90f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.90f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.50f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.80f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.86f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);

		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.20f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);

		style.Colors[ImGuiCol_Tab] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);


		style.Colors[ImGuiCol_PlotLines] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(p_TextColor.x, p_TextColor.y, p_TextColor.z, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(p_MainColor.x, p_MainColor.y, p_MainColor.z, 0.43f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(p_BackgroundColor.x, p_BackgroundColor.y, p_BackgroundColor.z, 0.92f);
	}
}