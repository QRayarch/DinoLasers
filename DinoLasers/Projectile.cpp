#include "Projectile.h"

Projectile::Projectile()
{
	damage = 10.0f;
	lifeTime = 0;
	maxLifeTime = 1.3f;
	speed = 40.0f;
	
	//
}

Projectile::Projectile(float laserDamage, float maxTime, float lzrSpeed)
{
	damage = laserDamage;
	lifeTime = 0;
	maxLifeTime = maxTime;
	speed = lzrSpeed;
}

void Projectile::OnTrigger(CollisionInfo info) {
	if (info.GetChecked()->IsTrigger()) return;
	Health* health = info.GetChecked()->GetGameObject()->GetComponent<Health>();
	if (health != nullptr) {
		health->TakeDamage(damage);
	}
	Rigidbody* body = info.GetChecked()->GetGameObject()->GetComponent<Rigidbody>();
	if (body != nullptr) {
		float amount = 10;
		body->SetVelocity(body->GetVelocity() + vector3(0.0f, amount, 0.0f) + GetGameObject()->GetTransform().GetForward() * amount);
	}
	GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
}

void Projectile::Update(float dt)
{
	lifeTime += dt;
	if (lifeTime >= maxLifeTime)
	{
		GameObjectManager::GetInstance()->RemoveGameObject(GetGameObject());
	}
}

void Projectile::SetGameObject(GameObject* gameObject) {
	Collideable::SetGameObject(gameObject);
	//Updateable::SetGameObject(gameObject);
	Rigidbody* rB = GetGameObject()->GetComponent<Rigidbody>();
	if (rB != nullptr) {
		//v = sp*forward of rB
		rB->SetVelocity(speed * GetGameObject()->GetTransform().GetForward());
	}
	GetGameObject()->GetTransform().SetOrentation(GetGameObject()->GetTransform().GetOrientation() * quaternion(vector3(0.0f, 0.0f, rand() % 360)));
	vector3 scale = vector3(1.0f, 1.0f, 12.0f);
	//GetGameObject()->GetTransform().SetScale(scale);
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
