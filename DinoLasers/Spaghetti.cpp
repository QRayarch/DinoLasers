#include "Spaghetti.h"

Spaghetti::Spaghetti()
{
}

Spaghetti::~Spaghetti()
{
}

void Spaghetti::OnCollide(CollisionInfo info) {
	GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
}
