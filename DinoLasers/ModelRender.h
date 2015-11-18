#pragma once
#include "RE\ReEngAppClass.h"
#include "Updateable.h"
#include "GameObject.h"

class ModelRender : virtual public Updateable
{
private:
	String model;
public:
	ModelRender(String, String);
	~ModelRender();

	void Update(float);

	String GetModel();
};

