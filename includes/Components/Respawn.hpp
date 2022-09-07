#pragma once
#include "Math.hpp"
#include "Core/Scene.hpp"
#include "Physics/RigidBody.hpp"

class Respawnable : public Core::DataStructure::MonoBehaviour
{
public:
	void Start() override;
	void Update() override;
	void Destroy() override;
	void DisplayGUI() override;

private:
	Core::myMath::Vec3 startPos;
	Physics::RigidBody* rb;
};
