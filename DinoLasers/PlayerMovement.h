#pragma once

#include "Updateable.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class PlayerMovement : public Updateable
{
private:
	float speed;
	sf::Vector2i prevMouse;
	sf::Vector2i currMouse;
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
	void Turn(float);
	void LookUp(float);
	void Update(float);
	void SetGameObject(GameObject*);

protected:
	void Init(void);
	void Swap(PlayerMovement&);
};

