#pragma once
#include "Updateable.h"
#include "GameObject.h"

class AnimateScale : virtual public Updateable
{
public:
	AnimateScale(vector3, vector3, float);
	~AnimateScale();

	void Update(float);
private:
	vector3  fromScale;
	vector3 toScale;
	float animateOver;
	float animateTimer;
};

