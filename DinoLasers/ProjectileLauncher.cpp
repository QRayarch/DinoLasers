#include "ProjectileLauncher.h"

ProjectileLauncher::ProjectileLauncher()
{

}

void ProjectileLauncher::LaunchProjectile()
{
	GameObject* projectile = new GameObject();
	projectile->AddComponent(new ModelRender("DinoLasers\\Laser.obj", "Laser"));
	Rigidbody* rgBody = new Rigidbody();
	rgBody->SetUseGravity(false);
	projectile->AddComponent(rgBody);
	projectile->AddComponent(new Projectile());
	//projectile->GetTransform().SetOrentation(quaternion(GetGameObject()->GetTransform().GetForward()));
	projectile->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition());
	GameObjectManager::GetInstance()->AddGameObject(projectile);
}

void ProjectileLauncher::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		LaunchProjectile();
}

ProjectileLauncher::~ProjectileLauncher()
{
}