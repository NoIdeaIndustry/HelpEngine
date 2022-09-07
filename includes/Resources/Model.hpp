#pragma once
#include "Resource.hpp"
#include <vector>
#include <Math.hpp>

namespace Resources
{

	class Model : public Resource
	{
	public :
		Model();
		~Model() {}

		void Load(const std::string& filepath) override;
		void Unload() override;

		void BindData();

		unsigned int VAO, VBO, EBO;
		unsigned int indexCount;

		std::vector<Core::myMath::Vec3> positions;
		std::vector<Core::myMath::Vec3> normals;
		std::vector<Core::myMath::Vec2> UVs;

		std::vector<unsigned int> triangles;
	private :
		void ParseVertex(const std::string& line);
		void ParseIndex(const std::string& line);



	};
}
