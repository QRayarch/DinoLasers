#include "Projectile.h"

Projectile::Projectile()
{
	damage = 10.0f;
	lifeTime = 0;
	maxLifeTime = 5.0f;
	speed = 20.0f;
}

Projectile::Projectile(float laserDamage, float maxTime, float lzrSpeed)
{
	damage = laserDamage;
	lifeTime = 0;
	maxLifeTime = maxTime;
	speed = lzrSpeed;
}


void Projectile::OnTrigger(CollisionInfo info) {
	info.GetChecked()->GetGameObject()->GetComponent<Health>()->TakeDamage(damage);
	//remove the component
}

void Projectile::Update(float dt)
{
	lifeTime += dt;
	if (lifeTime >= maxLifeTime)
	{
		//GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
	}
}

void Projectile::SetGameObject(GameObject* gameObject) {
	Collideable::SetGameObject(gameObject);
	//Updateable::SetGameObject(gameObject);
	Rigidbody* rB = GetGameObject()->GetComponent<Rigidbody>();
	if (rB != nullptr) {
		//v = sp*forward of rB
		rB->SetVelocity(speed * gameObject->GetTransform().GetForward());
	}
}

void Projectile::SetDamage(float newDamage)
{
	damage = newDamage;
}

void Projectile::SetMaxLifeTime(float newMax)
{
	maxLifeTime = newMax;
}

void Projectile::SetLifeTimer(float newTime)
{
	lifeTime = newTime;
}

Projectile::~Projectile()
{
}
