#pragma once

#include <string>

#include "Math.hpp"
#include "Resources/Model.hpp"
#include "LowRenderer/Camera.hpp"
#include "Resources/Material.hpp"
#include "ShaderProgram.hpp"
#include "Core/Scene.hpp"
#include "Resources/Texture.hpp"

namespace LowRenderer
{
	class Mesh : public Core::DataStructure::MonoBehaviour
	{
	public:
		Mesh(Resources::Model* _model, int _shdaerProgram);
		Mesh(Resources::Model* _model, int _shdaerProgram, Resources::Material* _mat);

		void Start() override;
		void Update() override;
		void Render();
		void DisplayGUI() override;
		void Destroy() override;

	private:
		Resources::Material* material;

		Resources::Model* model;
		int shaderProgram;
		Core::myMath::mat4x4 modelMatrix;
	};
}
