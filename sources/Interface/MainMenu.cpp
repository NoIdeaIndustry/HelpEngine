#include "Interface/MainMenu.hpp"

using namespace Resources;

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
	ImGui::Begin(" ");
	ImGui::SetWindowPos(ImVec2(700, 300), 0);
	ImGui::SetWindowSize(ImVec2(800, 600), 0);
	ImGui::SetWindowFontScale(2);
	ImGui::Dummy(ImVec2(250, 250));
	ImGui::Indent(200);
	TextCentered("Main Menu");

	if (ImGui::Button("Play", ImVec2(100,100))) {
		isPressedPlay = true;
		if (firstTime) {
			scene.Start();
		}
		firstTime = false;
	}
	ImGui::SameLine();

	if (ImGui::Button("Restart", ImVec2(100, 100))) {
		isPressedPlay = true;
		scene.Destroy();
		scene.Start();
		firstTime = false;
	}

	ImGui::SameLine();
	if (ImGui::Button("Options", ImVec2(100, 100))) {
		isPressedOptions = true;
	}

	ImGui::SameLine();
	if (ImGui::Button("Quit", ImVec2(100, 100))) {
		glfwSetWindowShouldClose(_window, true);
	}

	ImGui::End();
}

void MainMenu::DisplayGUIOptions() {
	ImGui::Begin(" ");
	ImGui::SetWindowPos(ImVec2(700, 300), 0);
	ImGui::SetWindowSize(ImVec2(800, 600), 0);
	ImGui::SetWindowFontScale(2);
	ImGui::Dummy(ImVec2(250, 250));
	ImGui::Indent(250);
	TextCentered("Options");

	if (ImGui::Button("Forward", ImVec2(120, 30))) {
		isWaitingToSelect = true;
		isNewKeyForward = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyForward));

	if (ImGui::Button("Left", ImVec2(120, 30))){
		isWaitingToSelect = true;
		isNewKeyLeft = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyLeft));

	if (ImGui::Button("Right", ImVec2(120, 30))) {
		isWaitingToSelect = true;
		isNewKeyRight = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyRight));

	if (ImGui::Button("Backward", ImVec2(120, 30))) {
		isWaitingToSelect = true;
		isNewKeyBackward = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyBackward));

	if (ImGui::Button("Jump", ImVec2(120, 30))) {
		isWaitingToSelect = true;
		isNewKeyJump = true;
	}
	ImGui::SameLine();
	ImGui::Text(ImGui::GetKeyName(Input::newKeyJump));

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
	ImGui::Text("Press ESC to go back");
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