#pragma once
#include "Collideable.h"
#include "Health.h"
#include "Rigidbody.h"
#include "AnimateScale.h"
#include "ModelRender.h"
#include "TimeRemover.h"

class LandMine : virtual public Collideable
{
public:
	LandMine(float);
	~LandMine();

	void OnCollide(CollisionInfo);
private: 
	float damage;
};

