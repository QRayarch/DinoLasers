#include "ProjectileLauncher.h"

ProjectileLauncher::ProjectileLauncher()
{
}

void ProjectileLauncher::LaunchProjectile()
{
	GameObject* projectile = new GameObject();
	projectile->AddComponent(new ModelRender("DinoLasers\\Laser.obj", "Laser"));
	projectile->AddComponent(new Rigidbody());
	projectile->AddComponent(new Projectile());
}

ProjectileLauncher::~ProjectileLauncher()
{
}