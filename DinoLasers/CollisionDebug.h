#pragma once
#include "Collideable.h"

class CollisionDebug :
	public Collideable
{
public:
	CollisionDebug();
	~CollisionDebug();

	void SetGameObject(GameObject*);

	void OnCollide(CollisionInfo);
	void OnCollideExit(CollisionInfo);
	void OnTrigger(CollisionInfo);
	void OnTriggerExit(CollisionInfo);
};

