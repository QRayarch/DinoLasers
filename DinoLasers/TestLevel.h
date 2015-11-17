#pragma once
#include "Level.h"
#include "CollisionDebug.h"

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
};

