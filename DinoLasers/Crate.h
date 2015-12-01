#pragma once
#include "DeathHandler.h"
#include "GameObjectManager.h"
#include "Health.h"

class Crate : public DeathHandler
{
public:
	Crate();
	~Crate();
	void OnDeath();
};

