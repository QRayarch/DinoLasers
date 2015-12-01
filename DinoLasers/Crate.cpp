#include "Crate.h"


Crate::Crate()
{
}

void Crate::OnDeath()
{
	//Why does this breakn everything?
	GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
}

Crate::~Crate()
{
}
