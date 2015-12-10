#include "EndScreen.h"


EndScreen::EndScreen(int s)
{
	score = s;
	needLoad = false;
}


EndScreen::~EndScreen()
{
	Level::~Level();
}

Level* EndScreen::NextLevel() {
	if (needLoad) {
		return new TitleScreen();
	}
	return this;
}

void EndScreen::Load() {
	needLoad = false;
	restartButton = new UIButton("Replay?", REWHITE, RERED);
	restartButton->SetPaddingX(30);
	restartButton->SetPaddingY(10);
	restartButton->SetInvisiblePaddingY(1);
	AddUIElement(restartButton);
	MeshManagerSingleton::GetInstance()->SetFont("Font.png");
}

void EndScreen::Update(float dt) {
	Level::Update(dt);
	if (restartButton->IsPressed()) {
		needLoad = true;
	}
	MeshManagerSingleton::GetInstance()->PrintLine("Dino Score: " + std::to_string(score), REMAGENTA);
}

void EndScreen::Render() {
	Level::Render();
}
