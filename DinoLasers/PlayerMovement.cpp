#include "PlayerMovement.h"

void PlayerMovement::Init(void)
{
	speed = 1.0f;
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

void PlayerMovement::MoveForward(void)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetForward() * speed);
}

void PlayerMovement::MoveBackward(void)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetForward() * -speed);
}

void PlayerMovement::StrafeRight(void)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetRight() * speed);
}

void PlayerMovement::StrafeLeft(void)
{
	GetGameObject()->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + GetGameObject()->GetTransform().GetRight() * -speed);
}

void PlayerMovement::Turn(void)
{

}

void PlayerMovement::LookUp(void)
{

}

void PlayerMovement::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
		MoveForward();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		MoveBackward();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		StrafeRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		StrafeLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		//playerRotation = quaternion(vector3(0.0f, glm::radians(1.0f), 0.0f)) * playerRotation;
		//forward = glm::rotate(REAXISZ, glm::angle(playerRotation), glm::axis(playerRotation));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		//playerRotation = quaternion(vector3(0.0f, glm::radians(-1.0f), 0.0f)) * playerRotation;
		//forward = glm::rotate(REAXISZ, glm::angle(playerRotation), glm::axis(playerRotation));
	}
}

float PlayerMovement::GetSpeed(void){ return speed; }
void PlayerMovement::SetSpeed(float s){ speed = s; }
