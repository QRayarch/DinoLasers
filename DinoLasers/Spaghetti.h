#pragma once
#include "Collideable.h"
#include "GameObjectManager.h"
#include "Rigidbody.h"

class Spaghetti : virtual public Collideable
{
public:
	Spaghetti();
	~Spaghetti();

	void OnCollide(CollisionInfo);
private:
};

