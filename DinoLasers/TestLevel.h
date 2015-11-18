#pragma once
#include "Level.h"
#include "CollisionDebug.h"
#include "Health.h"
#include "Crate.h"
#include "ProjectileLauncher.h"

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	void Load();
	void Update(float);
	void Render();
private :
	GameObject* dino;
	GameObject* test;
	std::vector<vector3> groundPoints;
};

