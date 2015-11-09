#pragma once
#include "RE\ReEngAppClass.h"
#include "Component.h"

class GameObject
{
private:
	matrix4 worldMatrix;
	std::map<String, Component*> components;
public:
	GameObject();
	GameObject(const GameObject&);
	~GameObject();
	GameObject& operator=(const GameObject&);

	void AddComponent(Component*);
	Component* GetComponent(String);
	std::map<String, Component*> GetComponents();

	matrix4 GetWorldMatrix();
	void SetWorldMatrix(matrix4);
};
