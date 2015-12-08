#include "GameObject.h"


GameObject::GameObject()
{
	components = std::vector<Component*>();
	transform = Transform();
}

GameObject::GameObject(const GameObject& other) {
	transform = other.transform;
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
	transform = other.transform;
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

Transform& GameObject::GetTransform() { return transform; }

void GameObject::SetTransform(Transform newTrans) { transform = newTrans; }

String GameObject::GetTag() { return tag; }
void GameObject::SetTag(String newTag){ tag = newTag; }

//Its a common call so if figured this could save some time
matrix4 GameObject::GetWorldMatrix() { return transform.GetMatrix(); }

