#pragma once
#include <iostream>
#include <fstream>

#include "Level.h"
#include "CollisionDebug.h"
#include "Health.h"
#include "Score.h"
#include "CrateDropper.h"
#include "ProjectileLauncher.h"
#include "EndScreen.h"
#include "ProgressBar.h"

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	Level* NextLevel();

	void Load();
	void Update(float);
	void Render();
private :
	bool needLoad;
	GameObject* dino;
	GameObject* crateDropper;
	std::vector<vector3> groundPoints;
	float gameTimer = 3 * 60;
	float maxGameTimer = 3 * 60;
	void LoadLevelFromFile(void);
};

