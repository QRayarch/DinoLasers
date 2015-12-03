#include "RandomMove.h"


RandomMove::RandomMove(float spd)
{
	speed = spd;
}


RandomMove::~RandomMove()
{
}

void RandomMove::SetGameObject(GameObject* gameObject) {
	Updateable::SetGameObject(gameObject);
	body = GetGameObject()->GetComponent<Rigidbody>();
}

void RandomMove::Update(float dt) {
	if (body == nullptr) {
		body = GetGameObject()->GetComponent<Rigidbody>();
	}
	else {
		if (rand() % 1000 < 10 ) {//|| glm::length(body->GetVelocity()) < 0.1f
			vector3 dir = vector3((rand() % 100 - 50) / 100.0f, 0.0f, (rand() % 100 - 50) / 100.0f);
			dir = glm::normalize(dir);
			body->SetAcceleration(dir * speed);
		}
	}
}

