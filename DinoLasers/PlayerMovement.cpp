#include "PlayerMovement.h"

void PlayerMovement::Init(void)
{	
	speed = 0.7f;
}
void PlayerMovement::Swap(PlayerMovement& other)
{
	std::swap(speed, other.speed);
}
PlayerMovement::PlayerMovement()
{
	Init();	
}

PlayerMovement::~PlayerMovement(){}
PlayerMovement::PlayerMovement(PlayerMovement const& other)
{
	speed = other.speed;
}
PlayerMovement& PlayerMovement::operator=(PlayerMovement const& other)
{
	if (this != &other)
	{
		Init();
		PlayerMovement temp(other);
		Swap(temp);
	}
	return *this;
}

void PlayerMovement::MoveForward(float dt)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetForward() * speed * dt);
}

void PlayerMovement::MoveBackward(float dt)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetForward() * -speed * dt);
}

void PlayerMovement::StrafeRight(float dt)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetRight() * speed * dt);
}

void PlayerMovement::StrafeLeft(float dt)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetRight() * -speed * dt);
}

void PlayerMovement::Turn(float degrees)
{
	GetGameObject()->GetTransform().SetOrentation(GetGameObject()->GetTransform().GetOrientation() * quaternion(glm::rotate(matrix4(IDENTITY_M4), degrees, REAXISY)));
}

void PlayerMovement::LookUp(float dt)
{

}

void PlayerMovement::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		MoveForward(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		StrafeLeft(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		MoveBackward(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		StrafeRight(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){ Turn(-1.0f);	}
		else { Turn(1.0f); }
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		//playerRotation = quaternion(vector3(0.0f, glm::radians(-1.0f), 0.0f)) * playerRotation;
		//forward = glm::rotate(REAXISZ, glm::angle(playerRotation), glm::axis(playerRotation));
	}
}

void PlayerMovement::SetGameObject(GameObject* g)
{
	Updateable::SetGameObject(g);
}

float PlayerMovement::GetSpeed(void){ return speed; }
void PlayerMovement::SetSpeed(float s){ speed = s; }
