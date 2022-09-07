#pragma once
#include "LowRenderer/Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "ShaderProgram.hpp"
#include "Math.hpp"

namespace LowRenderer
{
	class Renderer
	{
	public :
		static Camera* mainCamera;
		static std::vector<Light*> lights;
		static std::vector<Mesh*> meshList;
		static int shaderProgram;

		static void Update(); 
		static Core::myMath::mat4x4 modelViewMatrix;

	private :
	};
}