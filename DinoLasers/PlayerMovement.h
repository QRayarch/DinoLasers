#pragma once

#include "Updateable.h"
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class PlayerMovement : public Updateable
{
private:
	float speed;
public:
	PlayerMovement();
	PlayerMovement(PlayerMovement const&);
	~PlayerMovement();

	PlayerMovement& operator=(PlayerMovement const&);

	float GetSpeed(void);
	void SetSpeed(float s);
	void MoveForward(void);
	void MoveBackward(void);
	void StrafeRight(void);
	void StrafeLeft(void);
	void Turn(void);
	void LookUp(void);
	void Update(float dt);

protected:
	void Init(void);
	void Swap(PlayerMovement&);
};

