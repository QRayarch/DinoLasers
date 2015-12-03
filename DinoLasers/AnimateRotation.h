#pragma once
#include "Updateable.h"
#include "GameObject.h"

class AnimateRotation : virtual public Updateable
{
public:
	AnimateRotation(vector3);
	~AnimateRotation();

	void Update(float);
private:
	vector3 rotationRates;
};

