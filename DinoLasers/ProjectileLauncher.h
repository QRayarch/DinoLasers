#pragma once
#include "Component.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ModelRender.h"
#include "Projectile.h"
#include "Rigidbody.h"

class ProjectileLauncher : public Component
{
public:
	ProjectileLauncher();
	~ProjectileLauncher();

	void LaunchProjectile();
private:
};