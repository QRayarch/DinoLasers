#pragma once

#include "Component.h"
#include "CollisionInfo.h"

class Collideable : public Component
{
public:
	Collideable();
	~Collideable();

	virtual void OnCollide(CollisionInfo);
	virtual void OnCollideExit(CollisionInfo);
	virtual void OnTrigger(CollisionInfo);
	virtual void OnTriggerExit(CollisionInfo);
};

