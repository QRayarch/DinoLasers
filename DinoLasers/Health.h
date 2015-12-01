#pragma once
#include "Component.h"
#include "math.h"
#include "DeathHandler.h"
#include "GameObject.h"
#include "Crate.h"

class Health : public Component
{
private:
	float health;
	float maxHealth;
public:
	Health();
	Health(float);
	~Health();
	float GetHealth();
	void SetHealth(float);
	bool IsDead();
	void AddHealth(float);
	void TakeDamage(float);
};

