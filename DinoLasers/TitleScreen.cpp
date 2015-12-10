#include "TitleScreen.h"


TitleScreen::TitleScreen()
{
	needLoad = false;
}


TitleScreen::~TitleScreen()
{
	//TODO DEALLOCATE
	BoundingObjectManager::GetInstance()->SetGroundY(0.0f);
	Level::~Level();
}

Level* TitleScreen::NextLevel() {
	if (needLoad) {
		return new TestLevel();
	}
	return this;
}

void TitleScreen::Load() {
	BoundingObjectManager::GetInstance()->SetGroundY(-10.0f);
	GameObject* dino = new GameObject();
	dino->AddComponent(new ModelRender("DinoLasers\\Dino.obj", "Dino"));
	dino->GetTransform().SetPosition(vector3(0.7f * 7, -0.5f * 7, 0.0f));
	dino->GetTransform().SetOrentation(quaternion(vector3(-0.3f, -0.8f, 0.0f)));
	dino->GetTransform().SetScale(vector3(5.0f));
	GameObjectManager::GetInstance()->AddGameObject(dino);

	for (int s = 0; s < 3; s++) {
		GameObject* spat = new GameObject();
		spat->AddComponent(new ModelRender("DinoLasers\\Spaghetti.obj", "Spaghetti"));
		spat->GetTransform().SetPosition(vector3(0.1f + s * 0.4f + ((rand() % 2)) * 0.1f, -0.7f, 8.0f + (rand() % 2) - 1));
		spat->GetTransform().SetOrentation(quaternion(vector3(0.3f, 0.3f * s, 0.0f)));
		spat->GetTransform().SetScale(vector3(0.5f));
		GameObjectManager::GetInstance()->AddGameObject(spat);
	}
	timer = 0.0f;
	GameObject* lan = new GameObject();
	launcher = new ProjectileLauncher();
	lan->AddComponent(launcher);
	lan->GetTransform().SetOrentation(quaternion(vector3(glm::pi<float>()/2, 0.0f, 0.3f)));
	GameObjectManager::GetInstance()->AddGameObject(lan);


	for (int s = 0; s < 20; s++) {
		GameObject* mine = new GameObject();
		mine->AddComponent(new ModelRender("DinoLasers\\SpaghettiMine.obj", "Mine"));
		mine->GetTransform().SetPosition(vector3(((rand() % 20) - 10) * 1.0f, -1.7f, ((rand() % 20) - 10) * 1.0f));
		//mine->GetTransform().SetOrentation(quaternion(vector3(0.3f, 0.3f * s, 0.0f)));
		mine->GetTransform().SetScale(vector3(0.5f));
		Rigidbody* body = new Rigidbody();
		body->SetUseGravity(false);
		mine->AddComponent(body);
		mine->AddComponent(new RandomMove(10.1f));
		GameObjectManager::GetInstance()->AddGameObject(mine);
	}

	playButton = new UIButton("Play", REWHITE, RERED);
	playButton->SetPaddingX(30);
	playButton->SetPaddingY(10);
	AddUIElement(playButton);
	exitButton = new UIButton("Exit", REWHITE, RERED);
	exitButton->SetPaddingX(30);
	exitButton->SetPaddingY(1);
	exitButton->SetInvisiblePaddingY(10);
	AddUIElement(exitButton);
}

void TitleScreen::Update(float dt) {
	Level::Update(dt);
	if (playButton->IsPressed()) {
		needLoad = true;
	}
	if (exitButton->IsPressed()) {
		//PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL)
	}
	timer += dt;
	if (timer > 0.1f) {
		timer = 0.0f;
		launcher->LaunchProjectile();
		launcher->GetGameObject()->GetTransform().SetPosition(vector3((rand() % 10 - 5) * 0.4f, 8.0f, (rand() % 10 - 5) * 0.4f));
	}
}

void TitleScreen::Render() {
	Level::Render();
}
