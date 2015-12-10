#pragma once
#include "Level.h"
#include "TestLevel.h"
#include "UIButton.h"
#include "ProjectileLauncher.h"
#include "RandomMove.h"
#include "AnimateRotation.h"

class TitleScreen : public Level
{
public:
	TitleScreen();
	~TitleScreen();

	Level* NextLevel();
	void Load();
	void Update(float);
	//void PausedUpdate(float);
	void Render();
private: 
	bool needLoad;
	UIButton* playButton;
	UIButton* exitButton;
	ProjectileLauncher* launcher;
	float timer;
};

