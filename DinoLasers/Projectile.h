#pragma once
#include "Collideable.h"
#include "Rigidbody.h"
#include "Health.h"

class Projectile : public Collideable, public Updateable
{
private:
	float damage;
	float lifeTime;
	float maxLifeTime;
	float speed;
public:
	Projectile();
	Projectile(float, float, float);
	void SetSpeed(float);
	void SetMaxLifeTime(float);
	void SetLifeTimer(float);
	void SetGameObject(GameObject*);
	void SetDamage(float);
	void OnTrigger(CollisionInfo);
	~Projectile();
	void Update(float);
};

