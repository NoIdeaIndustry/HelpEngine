#pragma once

#include <vector>

#include "Math.hpp"
#include "Resource.hpp"

namespace Resources
{
	class Model : public Resource
	{
	public :
		Model(const std::string& _filepath = "");
		~Model() {}

		void Load() override;
		void Unload() override;

		void Bind() override;

		unsigned int VAO, VBO, EBO;
		unsigned int indexCount;

		std::vector<Core::myMath::Vec3> positions;
		std::vector<Core::myMath::Vec3> normals;
		std::vector<Core::myMath::Vec2> UVs;

		std::vector<unsigned int> triangles;

	private:
		void ParseVertex(const std::string& line);
		void ParseIndex(const std::string& line);
	};
}
