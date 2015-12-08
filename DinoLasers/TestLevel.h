#pragma once
#include <iostream>
#include <fstream>

#include "Level.h"
#include "CollisionDebug.h"
#include "Health.h"
#include "CrateDropper.h"
#include "ProjectileLauncher.h"

#include "ProgressBar.h"

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
	GameObject* crateDropper;
	std::vector<vector3> groundPoints;

	void LoadLevelFromFile(void);
};

