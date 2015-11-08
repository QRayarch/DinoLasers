#include "Component.h"


Component::Component()
{
}

Component::Component(const Component& other) {
	gameObject = other.gameObject;
}

Component::~Component()
{
}

GameObject Component::GetGameObject() {
	return gameObject;
}

void Component::SetGameObject(GameObject newGameObject) {
	gameObject = newGameObject;
}
