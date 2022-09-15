#pragma once

#include <IMGUI/includes/imgui.h>

namespace CustomInterface::CustomTheme
{
	class Theme
	{
	public:
		static void LoadDefaultTheme(const bool& s_EraseData);
		static void LoadGoldTheme(const bool& s_EraseData);

	private:
		inline static float p_BorderRoundness;
		inline static bool p_WindowsEditMode;

		inline static ImVec4 p_MainColor;
		inline static ImVec4 p_BackgroundColor;
		inline static ImVec4 p_TextColor;
		inline static ImVec4 p_FillArea;
	};
}