#include "ProjectileLauncher.h"
#include "CollisionDebug.h"

ProjectileLauncher::ProjectileLauncher()
{

}

void ProjectileLauncher::LaunchProjectile()
{
	GameObject* projectile = new GameObject();
	projectile->AddComponent(new ModelRender("DinoLasers\\Laser.obj", "Laser"));
	BoundingObject* boundingOb = new BoundingObject();
	boundingOb->SetLayer(4);
	boundingOb->SetIsTrigger(true);
	projectile->AddComponent(boundingOb);
	projectile->GetTransform().SetOrentation(GetGameObject()->GetTransform().GetOrientation());
	projectile->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + vector3(0.0f, 0.9f, 0.0f));
	Rigidbody* rgBody = new Rigidbody();
	rgBody->SetUseGravity(false);
	projectile->AddComponent(rgBody);
	projectile->AddComponent(new Projectile());
	GameObjectManager::GetInstance()->AddGameObject(projectile);
}

void ProjectileLauncher::Update(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		LaunchProjectile();
}

ProjectileLauncher::~ProjectileLauncher()
{
}