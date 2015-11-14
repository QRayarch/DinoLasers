#include "Rigidbody.h"

void Rigidbody::Init(void)
{
	maxAcceleration = 10;

	velocity = vector3();
	accerleration = vector3();

	mass = 1;
}
void Rigidbody::Swap(Rigidbody& other)
{
	std::swap(velocity, other.velocity);
	std::swap(accerleration, other.accerleration);

	std::swap(mass, other.mass);
	std::swap(maxAcceleration, other.maxAcceleration);
}

Rigidbody::Rigidbody()
{
	Init();
}


Rigidbody::Rigidbody(Rigidbody const& other)
{
	velocity = other.velocity;
	accerleration = other.accerleration;

	mass = other.mass;
	maxAcceleration = other.maxAcceleration;
}

Rigidbody::~Rigidbody()
{
	
}

Rigidbody& Rigidbody::operator=(Rigidbody const& other)
{
	if (this != &other)
	{
		Init();
		Rigidbody temp(other);
		Swap(temp);
	}
	return *this;
}

void Rigidbody::Update(float dt) 
{

	accerleration = glm::clamp(accerleration, -maxAcceleration, maxAcceleration);
	velocity += accerleration;

	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + velocity * (1 / mass));
}

void Rigidbody::SetVelocity(vector3 newVelo) { velocity = newVelo; }
void Rigidbody::SetAcceleration(vector3 newAcc) { accerleration = newAcc; }
void Rigidbody::SetMass(float newMass) { mass = newMass; }
