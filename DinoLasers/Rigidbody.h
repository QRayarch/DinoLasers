#pragma once
#include "RE\ReEng.h"
#include "Updateable.h"
#include "GameObject.h"

#define GRAVITY 3.5

class Rigidbody : public Updateable
{
	vector3 velocity;
	vector3 accerleration;
	float mass = 1;

	float maxAcceleration;

	bool useGravity;
public:
	Rigidbody();
	Rigidbody(Rigidbody const&);
	~Rigidbody();

	Rigidbody& operator=(Rigidbody const&);

	void Update(float);

	void SetVelocity(vector3);
	vector3 GetVelocity();
	void SetAcceleration(vector3);
	void SetMass(float);
	void SetUseGravity(bool);
protected:
	void Init(void);
	void Swap(Rigidbody&);
};

