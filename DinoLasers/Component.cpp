#include "Component.h"


Component::Component()
{
	gameObject = nullptr;
}

Component::Component(const Component& other) {
	gameObject = other.gameObject;
}

Component::~Component()
{
	if (gameObject != nullptr) {
//		delete gameObject;
//		gameObject = nullptr;
	}
}

GameObject* Component::GetGameObject() {
	return gameObject;
}

void Component::SetGameObject(GameObject* newGameObject) {
	if (gameObject != nullptr) {
		delete gameObject;
		gameObject = nullptr;
	}
	gameObject = newGameObject;
}
