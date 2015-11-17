#pragma once
#include "Component.h"

class Updateable : public Component
{
public:
	Updateable();
	~Updateable();

	virtual void Update(float) = 0;
};

