#pragma once

#include "ResourceManager.hpp"
#include "Resource.hpp"
#include "Texture.hpp"
#include "Math.hpp"

namespace Resources
{
	class Material : public Resource
	{
	public:
		Material(Texture* tex, Core::myMath::Vec3 color = Core::myMath::Vec3(), float shiny = 1);
		void Unload() override;

		void DisplayGUI(int index) override;

		Texture* albedoTexture;
		Core::myMath::Vec3 albedoColor;

		Core::myMath::Vec3 specularColor;

		float shininess;
	};
}
