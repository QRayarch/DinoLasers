#include "Crate.h"


Crate::Crate()
{
}

void Crate::OnDeath()
{
	GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
}

Crate::~Crate()
{
}
