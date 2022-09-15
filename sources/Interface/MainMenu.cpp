#include "Interface/MainMenu.hpp"
#include "Interface/Theme.hpp"
#include "Core/App.hpp"

using namespace Resources;
using namespace CustomInterface::CustomTheme;

const int GUI_WIDTH = 900;
const int GUI_HEIGHT = 250;

void MainMenu::Update() {
	if (isPressedPlay) {
		ResourceManager::DisplayGUI();
		scene.Update();
	}

	if (isPressedOptions) {
		DisplayGUIOptions();
	}
}

void MainMenu::DisplayGUI(GLFWwindow* _window) {
	isInMenu = true;
	Theme::LoadGoldTheme(true);

	bool l_ShowWindow;
	ImGui::Begin(" ", &l_ShowWindow, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);;
	ImGui::SetWindowPos(ImVec2((Core::App::p_AppSettings.APP_WIDTH - GUI_WIDTH)/2, (Core::App::p_AppSettings.APP_HEIGHT - GUI_HEIGHT)/2), 0);
	ImGui::SetWindowSize(ImVec2(GUI_WIDTH, GUI_HEIGHT), 0);
	ImGui::SetWindowFontScale(2);
	ImGui::Dummy(ImVec2(0, GUI_HEIGHT / 4));
	ImGui::Indent(GUI_WIDTH/18);

	TextCentered("Main Menu");

	if (ImGui::Button("Play", ImVec2(150, 100))) {
		isPressedPlay = true;
		if (firstTime) {
			scene.Start();
			isInMenu = false;
		}
		firstTime = false;
	}
	ImGui::SameLine();

	if (ImGui::Button("Restart", ImVec2(150, 100))) {
		isPressedPlay = true;
		scene.Destroy();
		ResourceManager::ReloadResources();
		scene.Start();
		firstTime = false;

	}

	ImGui::SameLine();
	if (ImGui::Button("Options", ImVec2(150, 100))) {
		isPressedOptions = true;
	}

	ImGui::SameLine();
	if (ImGui::Button("Quit", ImVec2(150, 100))) {
		glfwSetWindowShouldClose(_window, true);
	}

	std::string str = ResourceManager::asyncLoading ? "Async [ON]" : "Async [OFF]";
	const char* c = str.c_str();

	ImGui::SameLine();
	if (ImGui::Button(c, ImVec2(160, 100))) {
		ResourceManager::asyncLoading = !ResourceManager::asyncLoading;
		c = str.c_str();
	}
	ImGui::End();
}

void MainMenu::DisplayGUIOptions() {

	bool l_ShowWindow;
	ImGui::Begin(" ", &l_ShowWindow, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowPos(ImVec2((Core::App::p_AppSettings.APP_WIDTH - GUI_WIDTH) / 2, (Core::App::p_AppSettings.APP_HEIGHT - GUI_HEIGHT) / 2), 0);
	ImGui::SetWindowSize(ImVec2(GUI_WIDTH+50, GUI_HEIGHT), 0);
	ImGui::SetWindowFontScale(2);
	ImGui::Dummy(ImVec2(0, GUI_HEIGHT / 6));
	ImGui::Indent(GUI_WIDTH / 26);

	TextCentered("Options");

	if (ImGui::Button("Forward", ImVec2(120, 100))) {
		isWaitingToSelect = true;
		isNewKeyForward = true;

		ImGui::Text(ImGui::GetKeyName(Input::newKeyForward));
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyForward));


	ImGui::SameLine();
	if (ImGui::Button("Left", ImVec2(120, 100))){
		isWaitingToSelect = true;
		isNewKeyLeft = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyLeft));

	ImGui::SameLine();
	if (ImGui::Button("Right", ImVec2(120, 100))) {
		isWaitingToSelect = true;
		isNewKeyRight = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyRight));

	ImGui::SameLine();
	if (ImGui::Button("Backward", ImVec2(120, 100))) {
		isWaitingToSelect = true;
		isNewKeyBackward = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyBackward));

	ImGui::SameLine();
	if (ImGui::Button("Jump", ImVec2(120, 100))) {
		isWaitingToSelect = true;
		isNewKeyJump = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyJump));

	ImGui::Dummy(ImVec2(0, GUI_HEIGHT));
	TextCentered("Press ESC to go back");

	if (isWaitingToSelect && Input::IsAnyKeyDown()) {
		if (isNewKeyForward) {
			Input::newKeyForward = Input::GetLastKeyPressed();
		}
		if (isNewKeyLeft) {
			Input::newKeyLeft = Input::GetLastKeyPressed();
		}
		if (isNewKeyRight) {
			Input::newKeyRight = Input::GetLastKeyPressed();
		}
		if (isNewKeyBackward) {
			Input::newKeyBackward = Input::GetLastKeyPressed();
		}
		if (isNewKeyJump) {
			Input::newKeyJump = Input::GetLastKeyPressed();
		}

		isWaitingToSelect = false;
		isNewKeyForward = false;
		isNewKeyLeft = false;
		isNewKeyRight = false;
		isNewKeyBackward = false;
		isNewKeyJump = false;
	}

	ImGui::End();
}

void MainMenu::ReturnMainMenu(GLFWwindow* _window) {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		isPressedPlay = false;
		isPressedOptions = false;
	}
}

void MainMenu::TextCentered(std::string text) {
	float win_width = ImGui::GetWindowSize().x;
	float text_width = ImGui::CalcTextSize(text.c_str()).x;

	// calculate the indentation that centers the text on one line, relative
	// to window left, regardless of the `ImGuiStyleVar_WindowPadding` value
	float text_indentation = (win_width - text_width) * 0.5f;

	// if text is too long to be drawn on one line, `text_indentation` can
	// become too small or even negative, so we check a minimum indentation
	float min_indentation = 20.0f;
	if (text_indentation <= min_indentation) {
		text_indentation = min_indentation;
	}

	ImGui::SameLine(text_indentation);
	ImGui::PushTextWrapPos(win_width - text_indentation);
	ImGui::TextWrapped(text.c_str());
	ImGui::PopTextWrapPos();
}