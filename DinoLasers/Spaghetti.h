#pragma once
#include "Collideable.h"
#include "GameObjectManager.h"
#include "Rigidbody.h"
#include "Score.h"

class Spaghetti : virtual public Collideable
{
public:
	Spaghetti(float);
	~Spaghetti();

	void OnTrigger(CollisionInfo);
private:
	float points;
};

