#pragma once
#include "Updateable.h"
#include "GameObject.h"
#include "Rigidbody.h"

class RandomMove : virtual public Updateable
{
public:
	RandomMove(float);
	~RandomMove();

	void SetGameObject(GameObject*);

	void Update(float);
private :
	Rigidbody* body;
	float speed;
};

