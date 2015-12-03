#pragma once
#include "Collideable.h"
#include "Health.h"
#include "Rigidbody.h"

class LandMine : virtual public Collideable
{
public:
	LandMine(float);
	~LandMine();

	void OnCollide(CollisionInfo);
private: 
	float damage;
};

