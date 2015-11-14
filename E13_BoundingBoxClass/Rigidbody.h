#pragma once
#include "RE\ReEng.h"
#include "Updateable.h"
#include "GameObject.h"

class Rigidbody : public Updateable
{
	vector3 velocity;
	vector3 accerleration;
	float mass = 1;

	float maxAcceleration;

public:
	Rigidbody();
	Rigidbody(Rigidbody const&);
	~Rigidbody();

	Rigidbody& operator=(Rigidbody const&);

	void Update(float);

	void SetVelocity(vector3);
	void SetAcceleration(vector3);
	void SetMass(float);
protected:
	void Init(void);
	void Swap(Rigidbody&);
};

