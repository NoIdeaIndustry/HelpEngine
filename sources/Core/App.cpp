#include "Utils/Time.hpp"
#include "Core/App.hpp"
#include "Utils/Debug.hpp"
#include "Resources/Model.hpp"
#include "LowRenderer/Shader.hpp"
#include "Resources/Texture.hpp"
#include "LowRenderer/Mesh.hpp"
#include "Utils/Input.hpp"
#include "LowRenderer/Light.hpp"
#include "LowRenderer/ShaderProgram.hpp"
#include "LowRenderer/Renderer.hpp"
#include "Resources/Resource.hpp"
#include "Core/Scene.hpp"
#include "Interface/MainMenu.hpp"
#include <iostream>
#include <assert.h>
#include <Resources/ResourceManager.hpp>
#include <chrono>
#include <ctime>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "Physics/CollisionDisplay.hpp"
#include <thread>

#include "Utils//Save.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

using namespace Core;
using namespace Resources;
using namespace LowRenderer;

GLFWwindow* App::window;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	Core::App::p_AppSettings.APP_WIDTH = width;
	Core::App::p_AppSettings.APP_HEIGHT = height;
}

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}


void App::Init() {
	Data::SaveData save;
	save.Exist();

	if (!save.fileExist) {
		save.Create();
	}

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_AppSettings.APP_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_AppSettings.APP_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


	// glfw window creation
	// --------------------
	window = glfwCreateWindow(p_AppSettings.APP_WIDTH, p_AppSettings.APP_HEIGHT, p_AppSettings.APP_NAME, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		assert(false);
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert(false);
		return;
	}

	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	//Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//init Input System
	Input::Init(window);
}

void App::Update() {
#pragma region Shader

	/*ResourceManager::Create(new Shader(Shader::VERTEX, "resources\\Shaders\\VertexShader.vert"), "VertexShader", "resources\\Shaders\\VertexShader.vert");
	ResourceManager::Create(new Shader(Shader::FRAGMENT, "resources\\Shaders\\FragmentShader.frag"), "FragmentShader", "resources\\Shaders\\FragmentShader.frag");

	int vertShader = ((Shader*)ResourceManager::Get("VertexShader"))->shaderKey;
	int fragShader = ((Shader*)ResourceManager::Get("FragmentShader"))->shaderKey;

	ResourceManager::Create(new ShaderProgram(vertShader, fragShader), "ShaderProgram");*/
	

#pragma endregion
	
	ResourceManager::InitResourceMap();
	std::thread t{ ResourceManager::ReloadResources };


	MainMenu mainMenu;
	Core::Debug::Log::Init();

	Core::DataStructure::Scene scene;
	//scene.Start();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		//glfwGetWindowSize(window, &width, &height);
		ResourceManager::UpdateBinding();
		// input
			// -----
		glfwPollEvents();
		//processInput(window);
		Input::Update();

		// Time
		// ----
		Time::UpdateTime();

		// render
		// ------
		if(!mainMenu.isInMenu) 
			glClearColor(0.f, 0.f, 0.2f, 1.0f); 
		else
			glClearColor(0.f, 0.f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if(!mainMenu.isPressedPlay && !mainMenu.isPressedOptions) {
			mainMenu.DisplayGUI(window);
		}
		
		//Scene
		//scene.Update();
		mainMenu.ReturnMainMenu(window);

		mainMenu.Update();
		
		//ResourceManager::DisplayGUI();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		
	}

	t.join();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	

	// Delete all resources
	ResourceManager::Clear();
	scene.Destroy();

	glDeleteSamplers(1, &Resources::Texture::sampler);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}


void App::processInput(GLFWwindow* _window) {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);
}