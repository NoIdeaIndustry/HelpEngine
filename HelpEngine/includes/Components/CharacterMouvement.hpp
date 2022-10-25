#pragma once

#include "Core/Scene.hpp"
#include "Physics/RigidBody.hpp"

class CharacterMouvement : public Core::DataStructure::MonoBehaviour
{
public:
	void Start() override;
	void Update() override;
	void DisplayGUI() override;

	float movementSpeed = 20;
	float jumpHeight = 40;
	Physics::RigidBody* rb;
};