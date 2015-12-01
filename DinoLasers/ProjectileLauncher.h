#pragma once
#include "Updateable.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ModelRender.h"
#include "Projectile.h"
#include "Rigidbody.h"
#include <SFML\Graphics.hpp>
#include "Utility.h"

class ProjectileLauncher : public Updateable
{
public:
	ProjectileLauncher();
	~ProjectileLauncher();

	void LaunchProjectile();
	void Update(float);

	void SetFireTime(float);
private:
	std::vector<vector3> bounds;
	float fireTime;
	float fireTimer;
};