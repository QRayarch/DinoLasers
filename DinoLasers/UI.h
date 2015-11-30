#pragma once
#include "RE\ReEngAppClass.h"

class UI
{
public:
	UI(String);
	~UI();

	virtual void Update(float);
	virtual void Render() = 0;

	String GetName();
private:
	String name;
};

