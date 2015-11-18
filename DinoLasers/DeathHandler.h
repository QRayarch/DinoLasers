#pragma once
#include "Component.h"

class DeathHandler : public Component
{
public:
	DeathHandler();
	~DeathHandler();
	virtual void OnDeath() = 0;
};

