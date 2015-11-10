#pragma once
#include "RE\ReEngAppClass.h"
#include "Component.h"

class GameObject
{
private:
	matrix4 worldMatrix;
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

	matrix4 GetWorldMatrix();
	void SetWorldMatrix(matrix4);
};
