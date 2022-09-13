#pragma once

#include <vector>
#include <string>
#include <list>

#include "Math.hpp"

namespace Core::DataStructure
{
	class GameObject;

	class Transform
	{
	public:
		// In local coordinate
		Core::myMath::Vec3 position;
		Core::myMath::Vec3 rotation;
		Core::myMath::Vec3 scale = Core::myMath::Vec3(1, 1, 1);

		Core::myMath::Vec3 GetGlobalPosition();

		void Start();
		void Update();
		void DisplayGUI();

		Core::myMath::mat4x4 GetModel();
		GameObject* gameObject;
	};

	class MonoBehaviour
	{
	public:
		GameObject* gameObject;

		virtual void Start();
		virtual void Update();
		virtual void DisplayGUI();
		virtual void Destroy();
	};

	class GameObject
	{
	public:
		std::string name;

		Transform transform;

		void Start();
		void Update();
		void DisplayGUI();

		void AddComponent(MonoBehaviour* component);
		template<class T>
		inline T* GetComponent() {
			//if (std::is_base_of<MonoBehaviour, T>::value)
				//return nullptr;

			for (MonoBehaviour* component : components) {
				if (typeid(T) == typeid(*component)) {
					return (T*)component;
				}
			}
			return nullptr;
		}

		GameObject* GetParent();
		std::vector<GameObject*> GetChildren();
		void AddChildren(GameObject* object);
		void ShowInHierarchy(GameObject** selected);

		void Destroy();
		bool isDestroyed = false;

	private:
		std::vector<MonoBehaviour*> components;

		// Buffer to instantiate
		std::vector<MonoBehaviour*> componentsBuffer;

		GameObject* parent;
		std::vector<GameObject*> children;
	};

	class Scene
	{
	public:
		void Start();
		void Update();
		void Destroy();

		inline static Scene* currentScene;

		GameObject& Instantiate(std::string _name, GameObject* parent);
		GameObject& Instantiate(GameObject* object);
		GameObject& Instantiate(std::string _name, Core::myMath::Vec3 _position = Core::myMath::Vec3(), Core::myMath::Vec3 _rotation = Core::myMath::Vec3(), Core::myMath::Vec3 _scale = Core::myMath::Vec3(1, 1, 1));

	private:
		void DisplayGUI();
		void DisplayHierarchy(GameObject* currObject);

		std::vector<GameObject*> gameObjects;
		std::vector<GameObject*> rootGameObjects;
	};
}
