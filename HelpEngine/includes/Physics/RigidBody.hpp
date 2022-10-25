#pragma once

#include "Core/Scene.hpp"
#include "Math.hpp"

namespace Physics
{
	class RigidBody : public Core::DataStructure::MonoBehaviour
	{
	public:
		void Start() override;
		void Update() override;
		void DisplayGUI() override;
		void Destroy() override;

		void AddForce(Core::myMath::Vec3 force, bool continuous = false);

		Core::myMath::Vec3 velocity = Core::myMath::Vec3();

		float gravityScale = 10;
		float friction = 0.02f;

		static inline Core::myMath::Vec3 gravity = Core::myMath::Vec3(0, -9.81f, 0);

		bool isGrounded;

	private:

	};
}
