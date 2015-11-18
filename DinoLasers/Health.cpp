#include "Health.h"


Health::Health()
{
	health = 100;
	maxHealth = health;
}
Health::Health(float _health)
{
	health = _health;
	maxHealth = health;
}

float Health::GetHealth()
{
	return health;
}

void Health::SetHealth(float _newHealth)
{
	health = _newHealth;
}

void Health::AddHealth(float _increment)
{
	health += _increment;
	health = fmin(health, maxHealth);
}

void Health::TakeDamage(float _decriment)
{
	health -= _decriment;
	health = fmax(health, 0.0f);
}

bool Health::IsDead()
{
	return health <= 0.0f; 
}

Health::~Health()
{
}
