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
	std::map<String, Component*>::iterator iterator;
	for (iterator = components.begin(); iterator != components.end(); iterator++) {
		if (components[iterator->first] != nullptr) {
			delete components[iterator->first];
			components[iterator->first] = nullptr;
		}
	}
}

GameObject& GameObject::operator=(const GameObject& other) {
	worldMatrix = other.worldMatrix;
	components = other.components;
	return *this;
}

void GameObject::AddComponent(Component* newComponent) {
	String className = newComponent->GetType();
	if ((components[className] == nullptr)) {
		components[className] = newComponent;
	}
	else {
		printf("Trying to add a duplicate component type");
	}
}

matrix4 GameObject::GetWorldMatrix() {
	return worldMatrix;
}

void GameObject::SetWorldMatrix(matrix4 newWorldMatrix) {
	worldMatrix = newWorldMatrix;
}
