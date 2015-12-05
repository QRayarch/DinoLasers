#include "ProjectileLauncher.h"
#include "CollisionDebug.h"

ProjectileLauncher::ProjectileLauncher()
{
	fireTime = 1.0f;
	fireTimer = 0;
}

void ProjectileLauncher::LaunchProjectile()
{
	GameObject* projectile = new GameObject();
	ModelRender* model = new ModelRender("DinoLasers\\Laser.obj", "Laser");
	if (bounds.size() == 0) {
		bounds = Utility::GetModelMinMax(model->GetModel());
	}
	projectile->AddComponent(model);
	BoundingObject* boundingOb = new BoundingObject(bounds);
	boundingOb->SetLayer(4);
	boundingOb->SetIsTrigger(true);
	projectile->AddComponent(boundingOb);
	projectile->GetTransform().SetOrentation(GetGameObject()->GetTransform().GetOrientation());
	projectile->GetTransform().SetPosition(GetGameObject()->GetTransform().GetPosition() + vector3(0.0f, 0.9f, 0.0f) + GetGameObject()->GetTransform().GetForward());
	Rigidbody* rgBody = new Rigidbody();
	rgBody->SetUseGravity(false);
	projectile->AddComponent(rgBody);
	projectile->AddComponent(new Projectile());
	vector3 startScale = vector3(1.0f, 1.0f, 0.01f);
	projectile->GetTransform().SetScale(startScale);
	projectile->AddComponent(new AnimateScale(startScale, vector3(1.0f, 1.0f, 1.0f), 0.1f));
	GameObjectManager::GetInstance()->AddGameObject(projectile);
	projectile->GetTransform().RecalculateMatrix();
}

void ProjectileLauncher::Update(float dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (fireTimer >= fireTime) {
			LaunchProjectile();
			fireTimer = 0;
		}
	}
	fireTimer += dt;
}

ProjectileLauncher::~ProjectileLauncher()
{
}

void ProjectileLauncher::SetFireTime(float newFireTime) { fireTime = newFireTime; }