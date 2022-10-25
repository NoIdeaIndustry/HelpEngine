#pragma once

#include <vector>
#include <unordered_map>

#include "Math.hpp"
#include "Core/Scene.hpp"
#include "RigidBody.hpp"

namespace Physics
{
	struct CollisionHit {
		Core::myMath::Vec3 resolutionNormal;
		float resolutionDistance;
		bool isColliding;
	};

	class Collider :  public Core::DataStructure::MonoBehaviour
	{
	public:
		virtual Core::myMath::Vec3 FindFurthestPoint(const Core::myMath::Vec3& direction) const = 0;
		virtual void Render() const = 0;

		bool DrawCollider;

		RigidBody* rigidBody;
	};

	class SphereCollider :  public Collider
	{
	public:
		SphereCollider(float _radius = 1);

		Core::myMath::Vec3 FindFurthestPoint(const Core::myMath::Vec3& direction) const override;
		void Render() const override;

		void Start() override;
		void Update() override;
		void Destroy() override;
		void DisplayGUI() override;

		float radius = 1;
	};

	class CubeCollider : public Collider
	{
	public:
		Core::myMath::Vec3 FindFurthestPoint(const Core::myMath::Vec3& direction) const override;
		void Render() const override;

		void Start() override;
		void Update() override;
		void Destroy() override;
		void DisplayGUI() override;

	private:
		std::vector<Core::myMath::Vec3> vertices;
		Core::myMath::Vec3 size;
	};

	static class Collision
	{
	public:
		static inline std::vector<Collider*> colliders;
		static inline std::vector<RigidBody*> rigidBodies;

		static CollisionHit CheckCollision(const Collider& c1, const Collider& c2); // GJK Algorithm
		static CollisionHit ResolveCollision(const Collider& c1, const Collider& c2, const std::vector<Core::myMath::Vec3> simplex); // EPA Algorithm

		static void UpdateCollision();
	};
}

