#pragma once
#include "Component.h"

class Renderable : public Component
{
public:
	Renderable();
	~Renderable();

	virtual void Render() = 0;
};

