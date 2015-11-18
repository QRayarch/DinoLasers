#pragma once
#include "DeathHandler.h"

class Crate : public DeathHandler
{
public:
	Crate();
	~Crate();
	void OnDeath();
};

