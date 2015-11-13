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
	template<class T>
	T* GetComponent();
	std::vector<Component*> GetComponents();

	Transform& GetTransform();
	void SetTransform(Transform);

	matrix4 GetWorldMatrix();
};
