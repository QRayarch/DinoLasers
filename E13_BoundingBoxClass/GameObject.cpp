#include "GameObject.h"


GameObject::GameObject()
{
}

GameObject::GameObject(const GameObject& other) {
	worldMatrix = other.worldMatrix;
	components = other.components;
}


GameObject::~GameObject()
{
	for (int v = 0; v < components.size(); v++) {
		if (components[v] != nullptr) {
			delete components[v];
			components[v] = nullptr;
		}
	}
}

GameObject& GameObject::operator=(const GameObject& other) {
	worldMatrix = other.worldMatrix;
	components = other.components;
	return *this;
}

void GameObject::AddComponent(Component* newComponent) {
	newComponent->SetGameObject(this);
	components.push_back(newComponent);
}

std::vector<Component*> GameObject::GetComponents() {
	return components;
}

template<class T>
T* GameObject::GetComponent() {
	for (int v = 0; v < components.size(); v++) {
		T* comp = dynamic_cast<Updateable*>(components[v]);
		if (comp != nullptr) {
			return comp;
		}
	}
	return nullptr;
}

matrix4 GameObject::GetWorldMatrix() {
	return worldMatrix;
}

void GameObject::SetWorldMatrix(matrix4 newWorldMatrix) {
	worldMatrix = newWorldMatrix;
}
