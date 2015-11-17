#include "Rigidbody.h"

void Rigidbody::Init(void)
{
	maxAcceleration = 10;

	velocity = vector3();
	accerleration = vector3();

	mass = 1;

	useGravity = true;
}
void Rigidbody::Swap(Rigidbody& other)
{
	std::swap(velocity, other.velocity);
	std::swap(accerleration, other.accerleration);

	std::swap(mass, other.mass);
	std::swap(maxAcceleration, other.maxAcceleration);

	std::swap(useGravity, other.useGravity);
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

	useGravity = other.useGravity;
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

	if (useGravity) {
		velocity.y -= GRAVITY;
	}

	vector3 newPos = GetGameObject()->GetTransform().GetPosition();
	newPos += (velocity * (1 / mass)) * dt;

	GetGameObject()->GetTransform().SetPosition(newPos);
}

void Rigidbody::SetVelocity(vector3 newVelo) { velocity = newVelo; }
void Rigidbody::SetAcceleration(vector3 newAcc) { accerleration = newAcc; }
void Rigidbody::SetMass(float newMass) { mass = newMass; }
void Rigidbody::SetUseGravity(bool doesUseGravity) { useGravity = doesUseGravity; }
