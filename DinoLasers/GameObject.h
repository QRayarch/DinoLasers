#pragma once
#include "RE\ReEngAppClass.h"
#include "Transform.h"
#include "Component.h"

class GameObject
{
private:
	Transform transform;
	std::vector<Component*> components;
public:
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
	GameObject& operator=(const GameObject&);

	void AddComponent(Component*);
	std::vector<Component*> GetComponents();

	Transform& GetTransform();
	void SetTransform(Transform);

	matrix4 GetWorldMatrix();

	template<class T>
	T* GetComponent() {
		//if (!dynamic_cast<Component*>(T)) return nullptr;
		for (int v = 0; v < components.size(); v++) {
			T* comp = dynamic_cast<T*>(components[v]);
			if (comp != nullptr) {
				return comp;
			}
		}
		return nullptr;
	}

	template<class T>
	std::vector<T*> GetComponents() {
		std::vector<T*> comps;
		for (int v = 0; v < components.size(); v++) {
			T* comp = dynamic_cast<T*>(components[v]);
			if (comp != nullptr) {
				comps.push_back(comp);
			}
		}
		return comps;
	}
};
