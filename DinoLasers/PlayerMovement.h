#pragma once

#include "Updateable.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include "Rigidbody.h"
#include "Utility.h"

class PlayerMovement : public Updateable
{
private:
	float speed;	
	float sensitivity;
	sf::Vector2i currMouse;
	sf::Vector2i center;
public:
	PlayerMovement();
	PlayerMovement(PlayerMovement const&);
	~PlayerMovement();

	PlayerMovement& operator=(PlayerMovement const&);

	float GetSpeed(void);
	void SetSpeed(float);
	void MoveForward(float);
	void MoveBackward(float);
	void StrafeRight(float);
	void StrafeLeft(float);
	void Turn(float, float);
	void Update(float);
	void SetGameObject(GameObject*);

protected:
	void Init(void);
	void Swap(PlayerMovement&);
};

