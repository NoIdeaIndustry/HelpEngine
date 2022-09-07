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

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>

using namespace Core;
using namespace Resources;
using namespace LowRenderer;

GLFWwindow* App::window;

void App::Init(AppInitializer initializer)
{

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, initializer.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, initializer.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);


	// glfw window creation
	// --------------------
	window = glfwCreateWindow(initializer.width, initializer.height, initializer.name, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		assert(false);
		return;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, initializer.framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert(false);
		return;
	}


	GLint flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(initializer.glDebugOutput, nullptr);
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

void App::Update()
{

#pragma region Shader

	ResourceManager::Create(new Shader(Shader::VERTEX), "VertexShader", "Resources\\Shaders\\VertexShader.vert");
	ResourceManager::Create(new Shader(Shader::FRAGMENT), "FragmentShader", "Resources\\Shaders\\FragmentShader.frag");

	int vertShader = ((Shader*)ResourceManager::Get("VertexShader"))->shaderKey;
	int fragShader = ((Shader*)ResourceManager::Get("FragmentShader"))->shaderKey;

	ResourceManager::Create(new ShaderProgram(vertShader, fragShader), "ShaderProgram");
	
	
#pragma endregion

#pragma region Mesh

	using namespace std;
	
		
		
		ResourceManager::Create(new Model(), "Blaziken", "Resources\\Obj\\blaziken.obj");
		ResourceManager::Create(new Model(), "Bidoof", "Resources\\Obj\\Bidoof.obj");
		ResourceManager::Create(new Model(), "Cube", "Resources\\Obj\\cube.obj");
		ResourceManager::Create(new Model(), "Sphere", "Resources\\Obj\\sphere.obj");
		ResourceManager::Create(new Model(), "Boo", "Resources\\Obj\\boo.obj");
		ResourceManager::Create(new Model(), "Goomba", "Resources\\Obj\\goomba.obj");
		ResourceManager::Create(new Model(), "Maskass", "Resources\\Obj\\maskass.obj");

		
		CollisionDisplay::CollisionMesh::InitSphereMesh();
		CollisionDisplay::CollisionMesh::InitCubeMesh();
		
#pragma endregion

#pragma region Texture

		Texture::InitSampler();
		ResourceManager::Create(new Texture(), "Message", "Resources\\Textures\\Message_Icone.png");
		ResourceManager::Create(new Texture(), "Error", "Resources\\Textures\\Error_Icone.png");
		ResourceManager::Create(new Texture(), "Warning", "Resources\\Textures\\Warning_Icone.png");

		ResourceManager::Create(new Texture(), "BippaDh", "Resources\\Textures\\BippaDh.png");
		ResourceManager::Create(new Texture(), "dog", "Resources\\Textures\\sample2.png");
		ResourceManager::Create(new Texture(), "Blaziken Texture", "Resources\\Textures\\BlazikenTexture.png");
		ResourceManager::Create(new Texture(), "Goomba Texture", "Resources\\Textures\\goomba.png");
		ResourceManager::Create(new Texture(), "Boo Texture", "Resources\\Textures\\boo.png");
		ResourceManager::Create(new Texture(), "Maskass Texture", "Resources\\Textures\\heyho_tex_hr.png");
		ResourceManager::Create(new Texture(), "Ground Texture", "Resources\\Textures\\sol.png");


		
		ResourceManager::Create(new Material((Texture*)ResourceManager::Get("Goomba Texture"), Core::myMath::Vec3(1, 1, 1), 2), "goomba mat");
		ResourceManager::Create(new Material((Texture*)ResourceManager::Get("Ground Texture"), Core::myMath::Vec3(1, 1, 1), 2), "Ground Mat");

#pragma endregion
	MainMenu mainMenu;
	Core::Debug::Log::Init();

	Core::DataStructure::Scene scene;
	//scene.Start();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &width, &height);

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
		glClearColor(0.f, 0.f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if(!mainMenu.isPressedPlay && !mainMenu.isPressedOptions)
		{
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

	//Close log file();
	


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


void App::processInput(GLFWwindow* _window)
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);
}