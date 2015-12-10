#pragma once
#include "Level.h"
#include "TitleScreen.h"
#include "UIButton.h"

class EndScreen :
	public Level
{
public:
	EndScreen(int);
	~EndScreen();

	Level* NextLevel();
	void Load();
	void Update(float);
	void Render();

private:
	bool needLoad;
	UIButton* restartButton;
	int score;
};

