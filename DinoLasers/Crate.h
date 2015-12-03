#pragma once
#include "DeathHandler.h"
#include "GameObjectManager.h"
#include "Health.h"
#include "AnimateRotation.h"
#include "RandomMove.h"
#include "Rigidbody.h"
#include "LandMine.h"

class Crate : public DeathHandler
{
public:
	Crate();
	~Crate();
	void OnDeath();
};

