#pragma once
#include "Math.hpp"
#include "Core/Scene.hpp"


namespace LowRenderer
{
	class Camera : public Core::DataStructure::MonoBehaviour
	{
	public :
		Camera();

		
		float fov = 50;

		void Start() override;
		void Update() override;
		void DisplayGUI() override;

		void Render();

	private :
		void UpdateViewProjection();
		void ManageInput();
	};
}
