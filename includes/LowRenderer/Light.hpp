#pragma once
#include "Math.hpp"
#include "Core/Scene.hpp"

namespace LowRenderer
{
	class Light : public Core::DataStructure::MonoBehaviour
	{
	public :

		enum class LightType : int
		{
			L_DIRECTIONAL = 0,
			L_POINT = 1,
			L_SPOT = 2
		};

		Light(int _type);

		void Start() override;
		void Update() override;
		void DisplayGUI() override;
		void Render(int i);
		void Destroy() override;

		LightType type;
		
		float linearAttenuation, constantAttenuation, quadraticAttenuation;
		float spotCutoff;

		static Core::myMath::Vec4 ambientColor;
		Core::myMath::Vec3 color;
		float intensity;

	};
}