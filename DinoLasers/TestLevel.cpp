#include "TestLevel.h"


TestLevel::TestLevel()
{
	needLoad = false;
}


TestLevel::~TestLevel()
{
	Level::~Level();
}

Level* TestLevel::NextLevel() {
	if (needLoad) {
		int s = 0;
		Score* score = dino->GetComponent<Score>();
		if (score != nullptr) {
			s = score->GetScore();
		}
		return new EndScreen(s);
	}
	return this;
}

void TestLevel::Load() {
	//TEMP STUFF TO AVOID LAG
	GameObject* temp = new GameObject();
	ModelRender* tempModel = new ModelRender("DinoLasers\\Laser.obj", "Laser");
	temp->AddComponent(tempModel);
	temp->GetTransform().SetScale(vector3(0.0f, 0.0f, 0.0f));
	GameObjectManager::GetInstance()->AddGameObject(temp);
	temp = new GameObject();
	tempModel = new ModelRender("DinoLasers\\Spaghetti.obj", "Spaghetti");
	temp->AddComponent(tempModel);
	temp->GetTransform().SetScale(vector3(0.0f, 0.0f, 0.0f));
	GameObjectManager::GetInstance()->AddGameObject(temp);
	tempModel = new ModelRender("DinoLasers\\SpaghettiMine.obj", "Mine");
	temp->AddComponent(tempModel);
	temp->GetTransform().SetScale(vector3(0.0f, 0.0f, 0.0f));
	GameObjectManager::GetInstance()->AddGameObject(temp);
	tempModel = new ModelRender("DinoLasers\\Explosion.obj", "Explosion");
	temp->AddComponent(tempModel);
	temp->GetTransform().SetScale(vector3(0.0f, 0.0f, 0.0f));
	GameObjectManager::GetInstance()->AddGameObject(temp);
	//END TEMP STUFF


	dino = new GameObject();
	dino->AddComponent(new ModelRender("DinoLasers\\Dino.obj", "Dino"));
	BoundingObject* dinoBO = new BoundingObject();
	dinoBO->SetLayer(2 | 8);
	dino->AddComponent(dinoBO);
	dino->AddComponent(new CameraFollow());
	ProjectileLauncher* launcher = new ProjectileLauncher();
	launcher->SetFireTime(0.1f);
	dino->AddComponent(launcher);
	dino->AddComponent(new PlayerMovement());
	dino->AddComponent(new Rigidbody());
	dino->AddComponent(new Health());
	dino->AddComponent(new Score());
	dino->GetTransform().SetPosition(vector3(0.0f, 5.0f, 0.0f));
	//dino->AddComponent(new CollisionDebug());
	GameObjectManager::GetInstance()->AddGameObject(dino);

	crateDropper = new GameObject();
	crateDropper->AddComponent(new CrateDropper(1.0f, 20));
	GameObjectManager::GetInstance()->AddGameObject(crateDropper);
	
	/*Component* testModel = new ModelRender("DinoLasers\\SpaghettiMine.obj", "Mine");
	test = new GameObject();
	//test->AddComponent(testModel);
	test->GetTransform().SetPosition(vector3(0.0f, 1.0f, 0.0f));
	//BoundingObject* testBO = new BoundingObject();
	//test->AddComponent(testBO);
	GameObjectManager::GetInstance()->AddGameObject(test);*/

	ProgressBar* healthBar = new ProgressBar("Health", 100.0f);
	healthBar->SetFillColor(RERED);
	AddUIElement(healthBar);

	//maxGameTimer = gameTimer;
	ProgressBar* timerBar = new ProgressBar("Timer", maxGameTimer);
	timerBar->SetFillColor(REBLUE);
	AddUIElement(timerBar);

	//Load Level
	LoadLevelFromFile();
}

void TestLevel::LoadLevelFromFile() {
	std::ifstream levelFile("Levels\\0.txt", std::ios::in | std::ios::ate);
	if (levelFile.is_open()) {
		std::streampos size;
		char* levelInfo;

		size = levelFile.tellg();
		levelInfo = new char[size];
		levelFile.seekg(0, std::ios::beg);
		levelFile.read(levelInfo, size);
		levelFile.close();

		std::cout << "SIZE " << size << "\n";
		float gridSize = 2;
		int x = 0;
		int z = 0;
		CrateDropper* dropper = nullptr;
		bool wasLast = false;
		for (int c = 0; c < size; c++) {
			if (levelInfo[c] == '\n') {
				z++;
				x = 0;
				wasLast = true;
			}
			else {
				x++;
				switch (levelInfo[c]) {
					case 'N':
					case 'E':
					case 'S':
					case 'W':{
						GameObject* wall = new GameObject();
						wall->AddComponent(new ModelRender("DinoLasers\\Wall.obj", "Wall"));
						BoundingObject* wallBO = new BoundingObject();
						wallBO->SetLayer(2 | 4 | 8 | 16);
						wallBO->SetIsMoveable(false);
						wall->AddComponent(wallBO);
						if (!wasLast && (levelInfo[c - 1] == '#' || levelInfo[c + 1] == '#')) {
							//wallBO->SetIgnoreAxis(0);
							//wall->GetTransform().SetScale(vector3(0.8f));
						} else  {
							//wallBO->SetIgnoreAxis(2);
						}
						gridSize = wallBO->GetHalfWidth()[0] * 2;
						wall->GetTransform().SetPosition(vector3(static_cast<float>(x)* gridSize, 0.0f, static_cast<float>(z)* gridSize));
						//wall->GetTransform().SetOrentation(quaternion(vector3(0.0f, (rand() % 4) * glm::pi<float>() / 2, 0.0f)));
						//wallBO->SetIgnoreAxis(0);
						if (levelInfo[c] == 'N') {
							wallBO->SetIgnoreAxis(0);
						}
						else if (levelInfo[c] == 'E') {
							//wallBO->SetIgnoreAxis(0);
						}
						else if (levelInfo[c] == 'S') {
							wallBO->SetIgnoreAxis(2);
						}
						else if (levelInfo[c] == 'W') {
							wallBO->SetIgnoreAxis(8);
						}
						GameObjectManager::GetInstance()->AddGameObject(wall);
					}
					break;
					case 'D': {
						dino->GetTransform().SetPosition(vector3(static_cast<float>(x)* gridSize, 0.0f, static_cast<float>(z)* gridSize));
					}
					break;
					case 'C': {
						if (dropper == nullptr) {
							dropper = crateDropper->GetComponent<CrateDropper>();
						}
						dropper->AddSpawnPoint(vector3(static_cast<float>(x)* gridSize, 10.0f, static_cast<float>(z)* gridSize));
					}
					break;
				}
				wasLast = false;
			}
		}

		delete[] levelInfo;
	}
	else {
		std::cout << "ERROR LOADING FILE" << std::endl;
	}
}

void TestLevel::Update(float dt) {
	Level::Update(dt);

	if (gameTimer <= 0)
	{
		//game ends
		needLoad = true;
	}

	MeshManagerSingleton::GetInstance()->AddPlaneToQueue(glm::rotate(glm::translate(vector3(0.0f, BoundingObjectManager::GetInstance()->GetGroundY() - 1 - 0.2f, 0.0f)) * glm::scale(vector3(1000.0f)), 90.0f, vector3(1.0f, 0.0f, 0.0f)), REGRAY);
//	test->GetTransform().SetOrentation(test->GetTransform().GetOrientation() * quaternion(vector3(0.00f, 0.01f, 0.00f)));


	ProgressBar* bar = GetUIElement<ProgressBar>("Health");
	if (bar != nullptr) {
		Health* dinoHealth = dino->GetComponent<Health>();
		if (dinoHealth != nullptr) {
			bar->SetCurrentValue(dinoHealth->GetHealth());
		}
		if (dinoHealth->GetHealth() == 0) {
			needLoad = true;
		}
	}
	
	ProgressBar* tBar = GetUIElement<ProgressBar>("Timer");
	if (tBar != nullptr)
	{
		tBar->SetCurrentValue(gameTimer);
	}
	
	gameTimer -= dt;

	/*
	Score* playerScore = dino->GetComponent<Score>();
	if (playerScore != nullptr)
	{
		MeshManagerSingleton::GetInstance()->Print("Score: ");
		MeshManagerSingleton::GetInstance()->Print(std::to_string(playerScore->GetScore()));
	}
	*/
}

void TestLevel::Render() {
	Level::Render();
}
