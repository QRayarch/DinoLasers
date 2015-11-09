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
}

GameObject& GameObject::operator=(const GameObject& other) {
	worldMatrix = other.worldMatrix;
	components = other.components;
	return *this;
}

matrix4 GameObject::GetWorldMatrix() {
	return worldMatrix;
}

void GameObject::SetWorldMatrix(matrix4 newWorldMatrix) {
	worldMatrix = newWorldMatrix;
}
