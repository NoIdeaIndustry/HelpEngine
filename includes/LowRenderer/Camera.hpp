#pragma once

#include "Math.hpp"
#include "Core/Scene.hpp"

namespace LowRenderer
{
	class Camera : public Core::DataStructure::MonoBehaviour
	{
	public:
		Camera();
		void Start() override;
		void Update() override;
		void DisplayGUI() override;

		void Render();

		float fov = 50;

	private:
		void UpdateViewProjection();
		void ManageInput();
	};
}
